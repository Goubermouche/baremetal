workspace "assembler"
	architecture "x64"
	cppdialect "C++20"
	language "C++"

	configurations { "Release", "Debug" }
	flags { "MultiProcessorCompile" }

	buildoptions("-std=gnu++20", "-g", "-pedantic", "-Wall", "-Werror")
	startproject "tests"
	warnings "High"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		symbols "Off"

	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG" }
		symbols "On"
		optimize "Off"
		runtime "Debug"

	include "source/utility"

	project "assembler"
		kind "StaticLib"
		location "source/assembler"

		targetdir ("output/bin/%{prj.name}")
		objdir ("output/obj/%{prj.name}")

		files { "source/assembler/**.cpp", "source/assembler/**.h", "source/assembler/**.inc" }

		includedirs { "source", "source/utility/" }
		links { "utility" }

	project "test"
		kind "ConsoleApp"
		location "source/test"

		targetdir ("output/bin/%{prj.name}")
		objdir ("output/obj/%{prj.name}")

		files { "source/test/**.cpp", "source/test/**.h" }

		includedirs { "source", "source/utility/", "source/assembler" }
		links { "utility", "assembler" }

