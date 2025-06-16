workspace "YKLib"
  startproject "Test"

  configurations 
  {
    "Debug",
    "DebugDLL",
    "Release",
    "ReleaseDLL",
    "Final",
    "FinalDLL"
  }

  platforms 
  {
    "Win32",
    "Win64",
    "Linux",
    "MacOS"
  }

  flags { "MultiProcessorCompile" }

  -- Platform Filters
  filter { "platforms:Win32" }
    system "Windows"
    architecture "x86"
    systemversion "latest"
    defines { "PLATFORM_WINDOWS", "ARCH_X86", "_CRT_SECURE_NO_WARNINGS", "_SCL_SECURE_NO_WARNINGS", "NOMINMAX" }

  filter { "platforms:Win64" }
    system "Windows"
    architecture "x64"
    systemversion "latest"
    defines { "PLATFORM_WINDOWS", "ARCH_X64", "_CRT_SECURE_NO_WARNINGS", "_SCL_SECURE_NO_WARNINGS", "NOMINMAX" }

  filter { "platforms:Linux" }
    system "Linux"
    architecture "x64"
    defines { "PLATFORM_LINUX", "ARCH_X64" }
    buildoptions { "-std=c++20" }

  filter { "platforms:MacOS" }
    system "macosx"
    architecture "x64"
    defines { "PLATFORM_MACOS", "ARCH_X64" }

  -- Configuration Filters
  filter { "configurations:Debug" }
    symbols "On"
    optimize "Off"
    defines { "CONFIG_DEBUG" }

  filter { "configurations:DebugDLL" }
    symbols "On"
    optimize "Off"
    defines { "CONFIG_DEBUG", "YK_USE_DYNAMIC_LIB" }

  filter { "configurations:Release" }
    symbols "Off"
    optimize "Full"
    defines { "CONFIG_RELEASE" }

  filter { "configurations:ReleaseDLL" }
    symbols "Off"
    optimize "Full"
    defines { "CONFIG_RELEASE", "YK_USE_DYNAMIC_LIB" }

  filter { "configurations:Final" }
    symbols "Off"
    optimize "Full"
    defines { "CONFIG_FINAL" }

  filter { "configurations:FinalDLL" }
    symbols "Off"
    optimize "Full"
    defines { "CONFIG_FINAL", "YK_USE_DYNAMIC_LIB" }

  -- Reset filters
  filter {}

-- Include subprojects
group "Core"
include "YKLib"

group "Impl"
include "Test"

group ""