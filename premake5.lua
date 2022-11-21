workspace "Software 3D Renderer"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "NextAPI"
    location "NextAPI"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
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
        "%{prj.name}/**.c",
        "%{prj.name}/**.glsl"
    }

    postbuildcommands
    {
        ("{COPY} ../NextAPI/glut/binary/x64" .. " ../bin/" .. outputdir .. "/Executables")
    }
    
    links
    {
        "freeglut"
    }
    
    filter "system:windows"
        systemversion "latest"
    
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
    
    filter "files:**.c"
        flags {"NoPCH"}


project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")
    
    libdirs{"NextAPI/glut/lib"}
    includedirs{"NextAPI", "Engine/Tesla"}
    
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

    defines
    {
        "TS_ENGINE"
    }

    pchheader "TSPch.h"
    pchsource "Engine/TSPch.cpp"
    
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


project "Software 3D Renderer"
    location "Software 3D Renderer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/Executables")
    objdir ("int/" .. outputdir .. "/%{prj.name}")

    libdirs{"NextAPI/glut/lib"}
    includedirs{"Engine", "NextAPI"}

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.c"
    }

    links
    {
        "Engine",
        "freeglut"
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