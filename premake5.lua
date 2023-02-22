workspace "Project NEXT"
    architecture "x64"

    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    configurations
    {
        "Debug",
        "Release"
    }

    rtti("off")

    defines 
    {
        'RES_PATH="'.._MAIN_SCRIPT_DIR..'/GaussClient/res"',
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "WINDOWS"
        }
    filter "configurations:Debug"
        defines { "NEXT_DEBUG" }
        runtime "debug"
        optimize "off"
        symbols "on"

    filter "configurations:Development"
        defines { "NEXT_DEVELOPMENT" }
        runtime "release"
        optimize "debug"
        symbols "on"

    filter "configurations:Release"
        defines { "NEXT_RELEASE" }
        runtime "release"
        optimize "speed"
        symbols "off"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "NextAPI"
    location "NextAPI"
    kind "StaticLib"
    warnings "off"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")


    libdirs {"%{prj.location}/glut/lib/x64/"}
    includedirs{"%{prj.name}/glut/include"}

    
    pchheader "stdafx.h"
    pchsource "%{prj.name}/stdafx.cpp"

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.c"
    }

    postbuildcommands
    {
        ("{COPY} ../NextAPI/glut/binary/x64" .. " ../bin/" .. outputdir .. "/Executables")
    }
    
    links
    {
        "dsound",
        "dxguid",
        "freeglut"
    }
    
    filter "files:**.c"
        flags {"NoPCH"}


project "GaussEngine"
    location "GaussEngine"
    kind "StaticLib"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")
    
    libdirs{"NextAPI/glut/lib"}
    includedirs{"GaussEngine/src", "NextAPI"}

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.c"
    }
    
    links
    {
        "NextAPI",
        "freeglut"
    }

    pchheader "GSPch.h"
    pchsource "GaussEngine/GSPch.cpp"


project "GaussClient"
    location "GaussClient"
    kind "WindowedApp"

    targetdir ("bin/" .. outputdir .. "/Executables")
    objdir ("int/" .. outputdir .. "/%{prj.name}")

    libdirs{"NextAPI/glut/lib"}
    includedirs{"GaussEngine/src", "NextAPI"}

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.c"
    }

    links
    {
        "GaussEngine",
        "freeglut"
    }