include "premake5raylib.lua"
include "premake5chipmunk.lua"

project "cpwrlap"
	kind "StaticLib"
	language "C++"

	platform_defines()

	location "%{wks.location}/%{prj.name}"
	targetdir "%{wks.location}/bin/%{prj.name}/%{cfg.buildcfg}"

	filter "action:vs*"
		defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS"}
		characterset ("MBCS")

	filter{}

	includedirs
	{
		"raylib/src",
		"raylib/src/external/glfw/include",
		"Chipmunk2D/include/chipmunk",
		"include"
	}
	vpaths
	{
		["Header Files"] = { "include/**.h" },
		["Source Files/*"] = { "source/**.cpp" },
	}
	files { "include/**.h", "source/**.cpp" }

	filter{}

	link_raylib()

	links "chipmunk"