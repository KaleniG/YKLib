#include "YKLog.h"

#include <chrono>
#include <ctime>
#include <mutex>
#include <cstdio>
#include <cstdlib>

#if defined(PLATFORM_WINDOWS)
#include <Windows.h>
#else
#include <unistd.h>
#endif

namespace yk
{
#if defined(PLATFORM_WINDOWS)
  static HANDLE s_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

  static std::mutex s_LogMutex;

  namespace utils
  {
    static void OutputColoredMessage(const std::string& message, int32_t windowsColorCode, const char* posixColorCode)
    {
      auto now = std::chrono::system_clock::now();
      std::time_t t = std::chrono::system_clock::to_time_t(now);

      std::tm timeinfo;
#ifdef PLATFORM_WINDOWS
      localtime_s(&timeinfo, &t);
#else
      localtime_r(&t, &timeinfo);
#endif

      char timeBuffer[9];
      std::snprintf(timeBuffer, sizeof(timeBuffer), "%02d:%02d:%02d",
        timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

      std::lock_guard<std::mutex> lock(s_LogMutex);
      std::string finalMessage;

#if !defined(PLATFORM_WINDOWS)
      finalMessage.append(posixColorCode);
#else
      SetConsoleTextAttribute(s_ConsoleHandle, windowsColorCode);
#endif

      finalMessage.append("[");
      finalMessage.append(timeBuffer);
      finalMessage.append("] ");
      finalMessage.append(message);

#if !defined(PLATFORM_WINDOWS)
      finalMessage.append("\033[0m");
#endif

      finalMessage.append("\n");

#if defined(PLATFORM_WINDOWS)
      DWORD written;
      WriteConsoleA(s_ConsoleHandle, finalMessage.c_str(), static_cast<DWORD>(finalMessage.size()), &written, nullptr);
      SetConsoleTextAttribute(s_ConsoleHandle, 7);
#else
      write(STDOUT_FILENO, finalMessage.c_str(), finalMessage.size());
#endif
    }
  }

  void LogInfo(const std::string& message)
  {
    utils::OutputColoredMessage(message, 15 | (0 << 4), "\033[38;5;15m\033[48;5;0m");
  }

  void LogWarning(const std::string& message)
  {
    utils::OutputColoredMessage(message, 14 | (0 << 4), "\033[38;5;11m\033[48;5;0m");
  }

  void LogError(const std::string& message)
  {
    utils::OutputColoredMessage(message, 12 | (0 << 4), "\033[38;5;9m\033[48;5;0m");
  }

  void LogFatal(const std::string& message)
  {
    utils::OutputColoredMessage(message, 15 | (12 << 4), "\033[38;5;15m\033[48;5;9m");
  }

  void LogRuntimeError(const std::string& message)
  {
#if defined(PLATFORM_WINDOWS)
    MessageBoxA(NULL, message.c_str(), "Runtime Error", MB_OK | MB_ICONERROR);
#elif defined(PLATFORM_MACOS)
    std::string cmd = "osascript -e 'display alert \"Error\" message \"" + message + "\"'";
    std::system(cmd.c_str());
#endif
  }
}
