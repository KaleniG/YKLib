/*
============================================================
        H I G H - R E S O L U T I O N   P R O F I L E R
============================================================

This lightweight profiler generates a JSON trace compatible
with Chromium's built-in performance viewer (chrome://tracing).

FEATURES:
- Scoped timing with RAII-style profiling timers
- Multi-threaded support (thread ID included)
- Simple session management and output to JSON

USAGE:
1. Mark functions or scopes using:
     YK_PROFILE_FUNCTION();       // At function start
     YK_PROFILE_SCOPE("name");    // For specific code blocks

2. Wrap your program with session macros:
     YK_PROFILE_BEGIN_SESSION("Name", "output.json");
     // ... your code ...
     YK_PROFILE_END_SESSION();

Enable profiling by defining 'YK_ENABLE_PROFILING' at build time.

Designed for use in performance-critical applications or
debugging slow code paths with minimal overhead.
============================================================
*/

#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>

namespace yk 
{
  /// @brief Stores the result of a profiling measurement.
  struct ProfileResult 
  {
    const std::string Name;
    int64_t Start;
    int64_t End;
    uint32_t ThreadID;
  };

  /// @brief Manages profiling session and output.
  class Instrumentor 
  {
  public:
    ~Instrumentor();

    static void BeginSession(const std::string& name, const std::string& file_path = "results.json");
    static void EndSession();
    static void WriteProfile(const ProfileResult& result);
    static void WriteHeader();
    static void WriteFooter();

  private:
    Instrumentor() = default;

    static Instrumentor& GetInstance() 
    {
      static Instrumentor instance;
      return instance;
    }

    std::string m_SessionName = "None";
    std::ofstream m_OutputStream;
    int32_t m_ProfileCount = 0;
    std::mutex m_Mutex;
    bool m_ActiveSession = false;
  };

  /// @brief RAII-style timer that writes a profiling result upon destruction.
  class InstrumentationTimer 
  {
  public:
    explicit InstrumentationTimer(const std::string& name);
    ~InstrumentationTimer();

    void Stop();

  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
    ProfileResult m_Result;
    bool m_Stopped = false;
  };
}

#if defined(YK_ENABLE_PROFILING)

// Cross-platform function signature macro
#if defined(__GNUC__) || defined(__clang__)
#define YK_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define YK_FUNCTION_SIGNATURE __FUNCSIG__
#else
#define YK_FUNCTION_SIGNATURE __func__
#endif

/// @brief Starts a profiling session.
#define YK_PROFILE_BEGIN_SESSION(name, file_path) ::yk::Instrumentor::BeginSession(name, file_path)

/// @brief Ends the current profiling session.
#define YK_PROFILE_END_SESSION() ::yk::Instrumentor::EndSession()

/// @brief Internal macro for scoped timing with unique name per line.
#define YK_PROFILE_SCOPE_LINE(name, line) ::yk::InstrumentationTimer timer_line_##line(name)

/// @brief Profiles the current code scope using a named timer.
#define YK_PROFILE_SCOPE(name) YK_PROFILE_SCOPE_LINE(name, __LINE__)

/// @brief Profiles the current function using its signature as name.
#define YK_PROFILE_FUNCTION() YK_PROFILE_SCOPE(YK_FUNCTION_SIGNATURE)

#else

// Profiling disabled: macros expand to nothing
#define YK_PROFILE_BEGIN_SESSION(name, file_path)
#define YK_PROFILE_END_SESSION()
#define YK_PROFILE_SCOPE_LINE(name, line)
#define YK_PROFILE_SCOPE(name)
#define YK_PROFILE_FUNCTION(...)

#endif
