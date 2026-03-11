workspace "BAD"

	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "BAD"

	location "BAD"
	kind "SharedLib"
	language "C++"

	targetdir = "bin/" .. outdir .. "/%{prj.name}"
	objdir = "bin-int/" .. outdir .. "/%{prj.name}"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

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
			("{COPY} {cfg.buildtarget.relpath} ../bin/" .. outdir .. "/Sandbox")
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

	targetdir = "bin/" .. outdir .. "/%{prj.name}"
	objdir = "bin-int/" .. outdir .. "/%{prj.name}"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
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