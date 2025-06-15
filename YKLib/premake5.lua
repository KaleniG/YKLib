project "YKLib"
  language "C++"
  cppdialect "C++latest"
  staticruntime "On"
  kind "StaticLib"

  targetdir "../Bin/"
  objdir "../Bin-Int/"

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

  filter { "platforms:MacOS" }
    defines { "PLATFORM_MACOS", "ARCH_X64" }
    system "macosx"
    architecture "x64"

  filter { "configurations:Debug" }
    symbols "On"
    optimize "Off"
    defines { "CONFIG_DEBUG" }

  filter { "configurations:Release" }
    symbols "Off"
    optimize "Full"
    defines { "CONFIG_RELEASE" }

  filter { "configurations:Final" }
    symbols "Off"
    optimize "Full"
    defines { "CONFIG_FINAL" }