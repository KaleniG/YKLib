/*
============================================================
            H I G H   R E S O L U T I O N   T I M E R
============================================================

This lightweight utility provides simple and precise timing
tools for measuring elapsed time in milliseconds or seconds.

FEATURES:
- Manual timer with start/stop control
- Scoped RAII timer with virtual callback on finish
- Uses std::chrono high_resolution_clock for accuracy
- Suitable for quick benchmarking or debugging delays

USAGE:

1. Manual Timing:
   yk::Timer timer;
   timer.Start();
   // ... code ...
   timer.Stop();
   double ms = timer.ElapsedMilliseconds();

2. Scoped Timing:
   class MyScopedTimer : public yk::ScopedTimer 
   {
   protected:
     void OnFinish(double elapsed_ms) override 
     {
       // Handle timing result (e.g., log or store)
     }
   };

============================================================
*/

#pragma once

#include <cstdint>
#include <chrono>

#include "YKCore.h"

namespace yk
{
  /// @brief A manually controlled high-resolution timer.
  YK_API class Timer
  {
  public:
    /// @brief Starts the timer.
    YK_API void Start();
    /// @brief Stops the timer.
    YK_API void Stop();

    /// @brief Returns elapsed time in milliseconds.
    YK_API double ElapsedMilliseconds() const;
    /// @brief Returns elapsed time in seconds.
    YK_API double ElapsedSeconds() const;
    /// @brief Returns true if the timer is currently running.
    YK_API bool IsRunning() const { return m_Running; }

  private:
    bool m_Running = false;
    std::chrono::high_resolution_clock::time_point m_Start;
    std::chrono::high_resolution_clock::time_point m_End;
  };

  /// @brief A scoped timer that automatically reports elapsed time.
  ///
  /// Inherit this class and implement OnFinish() to handle the timing result.
  YK_API class ScopedTimer
  {
  public:
    YK_API ScopedTimer();
    YK_API ~ScopedTimer();

  protected:
    /// @brief Called when the scope ends. Override to process timing result.
    YK_API virtual void OnFinish(double elapsed_milliseconds) {}

  private:
    std::chrono::high_resolution_clock::time_point m_Start;
  };
}