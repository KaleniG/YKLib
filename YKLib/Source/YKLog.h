/*
============================================================
                       L O G G I N G
============================================================

A simple thread-safe logging utility for console output
with color-coded messages by severity.

FEATURES:
- Thread-safe output
- Timestamped log messages (HH:MM:SS format)
- Color-coded console output on Windows and POSIX terminals
- Supports Info, Warning, Error, and Fatal message levels

USAGE:
Include "YKLog.h" and call:
  yk::LogInfo("message");
  yk::LogWarning("message");
  yk::LogError("message");
  yk::LogFatal("message");
  yk::LogRuntimeError("message");

DESIGNED FOR:
Debugging and runtime diagnostics with minimal dependencies.

============================================================
*/

#pragma once

#include <string>

namespace yk
{
  /// @brief Logs an informational message to the console.
  void LogInfo(const std::string& message);

  /// @brief Logs a warning message to the console.
  void LogWarning(const std::string& message);

  /// @brief Logs an error message to the console.
  void LogError(const std::string& message);

  /// @brief Logs a fatal error message to the console.
  void LogFatal(const std::string& message);

  /// @brief Creates a platform specific message box displaying an error.
  void LogRuntimeError(const std::string& message);
}