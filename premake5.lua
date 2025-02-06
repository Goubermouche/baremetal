function get_version()
	-- MAJOR.TAG_COUNT.COMMIT_COUNT_IN_LAST_TAG
	-- total number of tags
	local tag_count_handle = io.popen("git tag | wc -l 2>/dev/null")
	local tag_count = tag_count_handle and tag_count_handle:read("*a") or "0"
	if tag_count_handle then tag_count_handle:close() end
	tag_count = tag_count:gsub("%s+", "")

	-- total number of commits since the last tag
	local commit_count_handle = io.popen("git rev-list  `git rev-list --tags --no-walk --max-count=1`..HEAD --count 2>/dev/null")
	local commit_count = commit_count_handle and commit_count_handle:read("*a") or "0"
	if commit_count_handle then commit_count_handle:close() end
	commit_count = commit_count:gsub("%s+", "")

	return string.format("\"0.%s.%s\"", tag_count, commit_count)
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

	defines { "VERSION=" .. get_version() }

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
