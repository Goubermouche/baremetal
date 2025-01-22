project "utility"
	kind "StaticLib"
	language "C++"
	targetdir "output/bin/utility"
	objdir "output/obj/utility"

	files { "utility/**.cpp", "utility/**.h" }
	includedirs { "utility/" }

