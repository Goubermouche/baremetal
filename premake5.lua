workspace "assembler"
    architecture "x64"
    cppdialect "C++20"
    language "C++"

    configurations { "Release", "Debug" }
    startproject "assembler"
    warnings "Extra"

    buildoptions { "-fsanitize=address" }
    linkoptions { "-fsanitize=address" }
    debugformat "C7"

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
        kind "ConsoleApp"
        location "source/assembler"

        targetdir ("output/bin/%{prj.name}")
        objdir ("output/obj/%{prj.name}")

        files { "source/assembler/**.cpp", "source/assembler/**.h" }

        includedirs { "source", "source/utility/" }
        links { "utility" }