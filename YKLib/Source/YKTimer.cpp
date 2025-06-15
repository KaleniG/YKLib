#include "YKTimer.h"

namespace yk
{
  void Timer::Start()
  {
    m_Start = std::chrono::high_resolution_clock::now();
    m_Running = true;
  }

  void Timer::Stop()
  {
    m_End = std::chrono::high_resolution_clock::now();
    m_Running = false;
  }

  double Timer::ElapsedMilliseconds() const
  {
    return std::chrono::duration<double, std::milli>((m_Running ? std::chrono::high_resolution_clock::now() : m_End) - m_Start).count();
  }

  double Timer::ElapsedSeconds() const
  {
    return Timer::ElapsedMilliseconds() / 1000.0;
  }

  ScopedTimer::ScopedTimer()
  {
    m_Start = std::chrono::high_resolution_clock::now();
  }

  ScopedTimer::~ScopedTimer()
  {
    double elapsed = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - m_Start).count();
    ScopedTimer::OnFinish(elapsed);
  }
}