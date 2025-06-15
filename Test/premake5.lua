project "Test"
  location "."
  language "C++"
  cppdialect "C++latest"
  staticruntime "On"
  kind "ConsoleApp"

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

  links
  {
    "YKLib"
  }

  filter { "platforms:MacOS" }
    files { "Source/**.mm" }

  filter "configurations:Final"
    symbols "Off"
    optimize "Full"
    kind "WindowedApp"
    entrypoint "mainCRTStartup"
    defines { "CONFIG_FINAL" }