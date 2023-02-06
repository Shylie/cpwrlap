project "chipmunk"
	kind "StaticLib"

	language "C"
	filter { "action:vs*", "files:Chipmunk2D/src/**.c" }
		compileas "C++"

	filter {}

	location "%{wks.location}/%{prj.name}"
	targetdir "%{wks.location}/bin/%{prj.name}/%{cfg.buildcfg}"

	defines
	{
		"CHIPMUNK_VERSION_MAJOR=7",
		"CHIPMUNK_VERSION_MINOR=0",
		"CHIPMUNK_VERSION_PATCH=3",
		"CHIPMUNK_VERSION=\"7.0.3\""
	}

    vpaths
    {
        ["Header Files"] = { "Chipmunk2D/include/chipmunk/**.h"},
        ["Source Files/*"] = { "Chipmunk2D/src/**.c" },
    }

	includedirs { "Chipmunk2D/include" }
	files { "Chipmunk2D/include/chipmunk/**.h", "Chipmunk2D/src/**.c" }