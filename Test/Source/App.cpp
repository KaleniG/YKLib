#include <thread>
#include <vector>
#include <string>

#if !defined(CONFIG_FINAL)
#define YK_ENABLE_DEBUG_LOG
#define YK_ENABLE_DEBUG_PROFILING_LOG
#endif

#define YK_ENABLE_PROFILING
#include <YKLib.h>

void SimulateWork(const std::string& taskName, int msDelay) 
{
  YK_PROFILE_SCOPE(taskName); // Profile this block
  YK_PROFILE_LOG("Finished task '{}'", taskName.c_str()); // Scoped log timing

  std::this_thread::sleep_for(std::chrono::milliseconds(msDelay));
  YK_INFO("Completed '{}', took approximately {}ms", taskName, msDelay);
}

void LoadAssets() 
{
  YK_PROFILE_FUNCTION(); // Profile entire function

  std::vector<std::pair<std::string, int>> assets = 
  {
      {"TextureAtlas", 100},
      {"AudioBank", 50},
      {"SceneData", 80},
      {"PlayerModel", 120},
      {"PhysicsMesh", 90}
  };

  for (const auto& [name, delay] : assets) 
    SimulateWork(name, delay);
}

void FaultyOperation() 
{
  int* ptr = nullptr;
  YK_ASSERT(ptr != nullptr, "Null pointer dereferenced in FaultyOperation");
}

int main() 
{
  yk::Timer globalTimer;
  globalTimer.Start();

  YK_PROFILE_BEGIN_SESSION("LoadSession", "profile_output.ykprofile");

  YK_INFO("Application started.");

  LoadAssets();

  YK_WARN("This is just a warning before something potentially risky.");

  YK_PROFILE_END_SESSION();

  globalTimer.Stop();
  double total = globalTimer.ElapsedMilliseconds();
  yk::LogInfo("Total runtime: " + std::to_string(total) + " ms");

  try 
  {
    FaultyOperation();
  }
  catch (...) 
  {
    YK_ERROR("Caught exception from faulty operation.");
  }

  YK_INFO("Application finished.");

  return 0;
}