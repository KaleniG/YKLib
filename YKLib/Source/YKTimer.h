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

namespace yk
{
  /// @brief A manually controlled high-resolution timer.
  class Timer 
  {
  public:
    /// @brief Starts the timer.
    void Start();
    /// @brief Stops the timer.
    void Stop();

    /// @brief Returns elapsed time in milliseconds.
    double ElapsedMilliseconds() const;
    /// @brief Returns elapsed time in seconds.
    double ElapsedSeconds() const;
    /// @brief Returns true if the timer is currently running.
    bool IsRunning() const { return m_Running; }

  private:
    bool m_Running = false;
    std::chrono::high_resolution_clock::time_point m_Start;
    std::chrono::high_resolution_clock::time_point m_End;
  };

  /// @brief A scoped timer that automatically reports elapsed time.
  ///
  /// Inherit this class and implement OnFinish() to handle the timing result.
  class ScopedTimer
  {
  public:
    ScopedTimer();
    ~ScopedTimer();

  protected:
    /// @brief Called when the scope ends. Override to process timing result.
    virtual void OnFinish(double elapsed_milliseconds) {}

  private:
    std::chrono::high_resolution_clock::time_point m_Start;
  };
}