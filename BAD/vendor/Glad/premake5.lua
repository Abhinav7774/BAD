project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "off"
	warnings "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "configurations:Debug"
		runtime "Debug"
		staticruntime "On"
		symbols "on"

	filter { "system:windows", "configurations:Debug-AS" }	
		runtime "Debug"
		staticruntime "On"
		symbols "on"
		sanitize { "Address" }
		runtimechecks "off"
		incrementallink "off"

	filter "configurations:Release"
		runtime "Release"
		optimize "speed"
		staticruntime "On"

    filter "configurations:Dist"
		runtime "Release"
		optimize "speed"
		staticruntime "On"
        symbols "off"
