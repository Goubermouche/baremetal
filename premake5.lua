function get_git_commit_count()
	local handle = io.popen("git rev-list --count HEAD 2>/dev/null")
	if handle then
		local result = handle:read("*a")
		handle:close()
		return result:gsub("%s+", "")
	end
	return "0"
end

workspace "assembler"
	architecture "x64"
	cppdialect "C++20"
	language "C++"

	configurations { "Release", "Debug" }
	flags { "MultiProcessorCompile" }

	buildoptions("-std=gnu++20", "-g", "-pedantic", "-Wall", "-Werror")
	startproject "tests"
	warnings "High"

	local patch_version = get_git_commit_count()
	local version = "0.1." .. patch_version
	defines { "VERSION=\"" .. version .. "\"" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		symbols "Off"

	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG" }
		symbols "On"
		optimize "Off"
		runtime "Debug"

	-- libs
	include "source/lib/utility"

	project "assembler"
		kind "StaticLib"
		location "source/lib/assembler"

		targetdir ("output/bin/%{prj.name}")
		objdir ("output/obj/%{prj.name}")

		files { "source/lib/assembler/**.cpp", "source/lib/assembler/**.h", "source/lib/assembler/**.inc" }

		includedirs { "source/lib", "source/lib/utility/" }
		links { "utility" }

	-- apps
	project "test"
		kind "ConsoleApp"
		location "source/app/test"

		targetdir ("output/bin/%{prj.name}")
		objdir ("output/obj/%{prj.name}")

		files { "source/app/test/**.cpp", "source/app/test/**.h" }

		includedirs { "source/lib", "source/lib/utility/", "source/lib/assembler" }
		links { "utility", "assembler" }

	project "basm"
		kind "ConsoleApp"
		location "source/app/basm"
		
		targetdir ("output/bin/%{prj.name}")
		objdir ("output/obj/%{prj.name}")
		
		files { "source/app/basm/**.cpp", "source/app/basm/**.h" }
		
		includedirs { "source/lib", "source/lib/utility/", "source/lib/assembler" }
		links { "utility", "assembler" }
