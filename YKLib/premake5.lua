project "YKLib"
  location "."
  language "C++"
  cppdialect "C++latest"
  staticruntime "On"

  targetdir "../Bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
  objdir "../Bin-Int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

  files
  {
    "Source/**.cpp",
    "Source/**.h",
    "premake5.lua"
  }

  includedirs
  {
    "Source"
  }

  filter { "platforms:Win32" }
    defines { "PLATFORM_WINDOWS", "ARCH_X86", "_CRT_SECURE_NO_WARNINGS", "_SCL_SECURE_NO_WARNINGS", "NOMINMAX" }
    system "Windows"
    systemversion "latest"
    architecture "x86"

  filter { "platforms:Win64" }
    defines { "PLATFORM_WINDOWS", "ARCH_X64", "_CRT_SECURE_NO_WARNINGS", "_SCL_SECURE_NO_WARNINGS", "NOMINMAX" }
    system "Windows"
    systemversion "latest"
    architecture "x64"

  filter { "platforms:Linux" }
    defines { "PLATFORM_LINUX", "ARCH_X64" }
    system "Linux"
    architecture "x64"
    buildoptions { "-std=c++20" }

  filter { "platforms:MacOS" }
    --files { "Source/**.mm" }
    defines { "PLATFORM_MACOS", "ARCH_X64" }
    system "macosx"
    architecture "x64"

  filter { "configurations:Debug" }
    symbols "On"
    optimize "Off"
    defines { "CONFIG_DEBUG" }
    kind "StaticLib"
    runtime "Debug"

  filter { "configurations:DebugDLL" }
    symbols "On"
    optimize "Off"
    defines { "CONFIG_DEBUG", "YK_USE_DYNAMIC_LIB", "YK_BUILD_DYNAMIC_LIB" }
    kind "SharedLib"
    runtime "Debug"

  filter { "configurations:Release" }
    symbols "Off"
    optimize "Full"
    defines { "CONFIG_RELEASE" }
    kind "StaticLib"
    runtime "Release"

  filter { "configurations:ReleaseDLL" }
    symbols "Off"
    optimize "Full"
    defines { "CONFIG_RELEASE", "YK_USE_DYNAMIC_LIB", "YK_BUILD_DYNAMIC_LIB" }
    kind "SharedLib"
    runtime "Release"

  filter { "configurations:Final" }
    symbols "Off"
    optimize "Full"
    defines { "CONFIG_FINAL" }
    kind "StaticLib"
    runtime "Release"

  filter { "configurations:FinalDLL" }
    symbols "Off"
    optimize "Full"
    defines { "CONFIG_FINAL", "YK_USE_DYNAMIC_LIB", "YK_BUILD_DYNAMIC_LIB" }
    kind "SharedLib"
    runtime "Release"