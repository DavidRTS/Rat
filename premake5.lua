workspace "Rat"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Rat"
	location "Rat"
	kind "SharedLib"
	language"C++"

	targetdir("bin/" ..outputdir.. "/%{prj.name}")
	objdir("bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"Rat",
		"glm",
		"nlohmann"
	}

	links
	{

	}

	pchheader "RTHeader.h"
	pchsource "Rat/RTHeader.cpp"


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RT_PLATFORM_WINDOWS",
			"RT_BUILD_DLL",
			"RAT_API"
		}

		postbuildcommands
		{
		    --"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Interactor"
		}

	filter "configurations:Debug"
		defines "RT_DEBUG"
		symbols "On"

	filter "configurations:Release"
			defines "RT_RELEASE"
			optimize "On"