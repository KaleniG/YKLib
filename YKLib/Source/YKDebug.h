/*
============================================================
                        DEBUG LOGGING
============================================================

Lightweight logging macros with formatted output and
conditional compilation support.

FEATURES:
- Conditional debug break on assert failure
- Info, Warning, Error, and Fatal log levels
- Uses std::format for formatting log messages
- Platform-specific debug break support
- Optional scoped timing for logging elapsed durations

USAGE:
1. Use macros to log messages with formatting:
     YK_INFO("Hello, {}!", "world");
     YK_WARN("Value is {}", value);
     YK_ERROR("Error code: {}", errorCode);
     YK_ASSERT(ptr != nullptr, "Pointer was null");

2. Use scoped profiling macro to log execution time:
     {
         YK_TIMED_INFO("Finished loading assets.");
         LoadAssets();
     }

3. Enable logging by defining YK_ENABLE_DEBUG_LOG
   (e.g., in your build system or globally via config)

4. Debug break triggers on failed assertions

============================================================
*/

#pragma once

#include <format>

#include "YKTimer.h"
#include "YKLog.h"

#if defined(YK_ENABLE_DEBUG_LOG)

// Cross-platform debug break macro
#if defined(PLATFORM_WINDOWS)
#define YK_DEBUG_BREAK() __debugbreak()
#else
#include <csignal>
#define YK_DEBUG_BREAK() raise(SIGTRAP)
#endif

/// @brief Logs an informational message (e.g., status or success).
#define YK_INFO(fmt, ...) \
{ \
    std::string message = std::format(fmt, ##__VA_ARGS__); \
    yk::LogInfo(message); \
}

/// @brief Logs a warning message (e.g., suspicious but recoverable).
#define YK_WARN(fmt, ...) \
{ \
    std::string message = std::format(fmt, ##__VA_ARGS__); \
    yk::LogWarning(message); \
}

/// @brief Logs an error message (e.g., non-fatal runtime error).
#define YK_ERROR(fmt, ...) \
{ \
    std::string message = std::format(fmt, ##__VA_ARGS__); \
    yk::LogError(message); \
}

/// @brief Asserts a condition, logs a fatal error, and breaks if false.
#define YK_ASSERT(x, fmt, ...) \
{ \
    if (!(x)) { \
        std::string message = std::format(fmt, ##__VA_ARGS__); \
        yk::LogFatal(message); \
        YK_DEBUG_BREAK(); \
    } \
}

#if defined(YK_ENABLE_DEBUG_PROFILING_LOG)
// Internal helper macros to generate unique names using line numbers
#define YK_CONCAT_IMPL(x, y) x##y
#define YK_CONCAT(x, y) YK_CONCAT_IMPL(x, y)

/// @brief Times the enclosing scope and logs the duration as an info message.
#define YK_PROFILE_LOG(fmt, ...) \
struct YK_CONCAT(ProfileTimer_, __LINE__) : public yk::ScopedTimer \
{ \
    std::string msg; \
    explicit YK_CONCAT(ProfileTimer_, __LINE__)(std::string m) : msg(std::move(m)) {} \
protected: \
    void OnFinish(double ms) override \
    { \
        std::string finalMsg = "[" + std::to_string(ms) + "ms] " + msg; \
        yk::LogInfo(finalMsg); \
    } \
} YK_CONCAT(_profileTimer_instance_, __LINE__)(std::format(fmt, ##__VA_ARGS__));


#endif

#else 

// Debug logging disabled: macros expand to nothing
#define YK_INFO(...)
#define YK_WARN(...)
#define YK_ERROR(...)

// Only asserts are still enabled and transformed into runtime errors, when available on the platform
#define YK_ASSERT(x, fmt, ...) \
{ \
    if (!(x)) { \
        std::string message = std::format(fmt, ##__VA_ARGS__); \
        yk::LogRuntimeError(message); \
    } \
}

#define YK_PROFILE_LOG(...)

#endif