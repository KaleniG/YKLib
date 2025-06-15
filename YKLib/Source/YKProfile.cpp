#include "YKProfile.h"

namespace yk
{
  Instrumentor::~Instrumentor()
  {
    Instrumentor& instance = Instrumentor::GetInstance();
    instance.EndSession();
  }

  void Instrumentor::BeginSession(const std::string& name, const std::string& file_path)
  {
    Instrumentor& instance = Instrumentor::GetInstance();

    if (instance.m_ActiveSession)
      instance.EndSession();

    instance.m_ActiveSession = true;
    instance.m_OutputStream.open(file_path);
    instance.WriteHeader();
    instance.m_SessionName = name;
  }

  void Instrumentor::EndSession()
  {
    Instrumentor& instance = Instrumentor::GetInstance();

    if (!instance.m_ActiveSession)
      return;

    instance.m_ActiveSession = false;
    instance.WriteFooter();
    instance.m_OutputStream.close();
    instance.m_ProfileCount = 0;
  }

  void Instrumentor::WriteProfile(const ProfileResult& result)
  {
    Instrumentor& instance = Instrumentor::GetInstance();
    std::lock_guard<std::mutex> lock(instance.m_Mutex);

    if (instance.m_ProfileCount++ > 0)
      instance.m_OutputStream << ",";

    std::string name = result.Name;
    std::replace(name.begin(), name.end(), '"', '\'');

    instance.m_OutputStream << "{";
    instance.m_OutputStream << "\"cat\":\"function\",";
    instance.m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
    instance.m_OutputStream << "\"name\":\"" << name << "\",";
    instance.m_OutputStream << "\"ph\":\"X\",";
    instance.m_OutputStream << "\"pid\":0,";
    instance.m_OutputStream << "\"tid\":" << result.ThreadID << ",";
    instance.m_OutputStream << "\"ts\":" << result.Start;
    instance.m_OutputStream << "}";
  }

  void Instrumentor::WriteHeader()
  {
    Instrumentor& instance = Instrumentor::GetInstance();
    instance.m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
  }

  void Instrumentor::WriteFooter()
  {
    Instrumentor& instance = Instrumentor::GetInstance();
    instance.m_OutputStream << "]}";
  }

  InstrumentationTimer::InstrumentationTimer(const std::string& name)
    : m_Result(ProfileResult{ name, 0, 0, 0 }), m_Stopped(false)
  {
    m_StartTimePoint = std::chrono::high_resolution_clock::now();
  }

  InstrumentationTimer::~InstrumentationTimer()
  {
    if (!m_Stopped)
    {
      InstrumentationTimer::Stop();
    }
  }

  void InstrumentationTimer::Stop()
  {
    std::chrono::high_resolution_clock::time_point endTimePoint = std::chrono::high_resolution_clock::now();

    m_Result.Start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
    m_Result.End = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
    m_Result.ThreadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
    Instrumentor::WriteProfile(m_Result);

    m_Stopped = true;
  }
}