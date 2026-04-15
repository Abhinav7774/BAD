workspace "BAD"

	architecture "x64"
	startproject "Sandbox"



	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "BAD/vendor/GLFW/include"

filter "system:windows"
        buildoptions { "/utf-8" }

include "BAD/vendor/GLFW"
include "BAD/vendor/Glad"

project "BAD"

	location "BAD"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .."/%{prj.name}")
	objdir("bin-int/".. outputdir .."/%{prj.name}")

	pchheader "badpch.h"
	pchsource "BAD/src/badpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"BAD/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/Glad/include",
		"%{prj.name}/vendor/GLFW/include"

	}
	
	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	dependson { "GLFW" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BAD_PLATFORM_WINDOWS",
			"BAD_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "BAD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BAD_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "BAD_DIST"
		optimize "On"
				
project "Sandbox"

	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir("bin/" .. outputdir .."/%{prj.name}")
	objdir("bin-int/".. outputdir .."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"BAD/vendor/spdlog/include",
		"BAD/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BAD_PLATFORM_WINDOWS"
		}

		links
		{
			"Glad",
			"BAD"
		}

	filter "configurations:Debug"
		defines "BAD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BAD_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "BAD_DIST"
		optimize "On"