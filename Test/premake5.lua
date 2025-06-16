project "Test"
  location "."
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++latest"
  staticruntime "On"

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
    "Source",
    "../YKLib/Source"
  }

  links { "YKLib" }

  filter { "platforms:MacOS" }
    --files { "Source/**.mm" }

  filter { "configurations:Debug*" }
    runtime "Debug"

  filter { "configurations:Release*" }
    runtime "Release"

  filter { "configurations:Final*" }
    kind "WindowedApp"
    entrypoint "mainCRTStartup"
    runtime "Release"

  filter {}