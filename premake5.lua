workspace "assembler"
    architecture "x64"
    -- cppdialect "C++20"
    language "C++"

    configurations { "Release", "Debug" }
    startproject "tests"
    warnings "Extra"

    -- buildoptions { "-fsanitize=address" }
    -- linkoptions { "-fsanitize=address" }
    -- debugformat "C7"

    buildoptions("-std=gnu++20", "-g")

    flags {
        "MultiProcessorCompile"
    }

    filter "toolset:gcc or clang"
        buildoptions { "-Wno-comment", "-Wno-missing-field-initializers" }

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        symbols "Off"

    filter "configurations:Debug"
        symbols "On"
        optimize "Off"
        runtime "Debug"
        defines { "DEBUG", "_DEBUG" }

    include "source/utility"

    project "assembler"
        kind "StaticLib"
        location "source/assembler"

        targetdir ("output/bin/%{prj.name}")
        objdir ("output/obj/%{prj.name}")

        files { "source/assembler/**.cpp", "source/assembler/**.h", "source/assembler/**.inc" }

        includedirs { "source", "source/utility/" }
        links { "utility" }

    project "test_runner"
        kind "ConsoleApp"
        location "source/test_runner"

        targetdir ("output/bin/%{prj.name}")
        objdir ("output/obj/%{prj.name}")

        files { "source/test_runner/**.cpp", "source/test_runner/**.h" }

        includedirs { "source", "source/utility/", "source/assembler" }
        links { "utility", "assembler" }

  filter "toolset:g++ or clang"
    buildoptions("-Wa", "-mbig-obj")
  filter "toolset:msvc"
        buildoptions("/bigobj")

