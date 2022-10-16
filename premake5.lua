
workspace "Caffeine" 
    configurations { "Debug","Release" } 
   
    project "DataStructures"   
        kind "StaticLib"  
        language "C"   
        
        targetdir "build/%{prj.name}/bin/%{cfg.buildcfg}"
        objdir "build/%{prj.name}/obj/%{cfg.buildcfg}"
        
        files { "sources/**.h","sources/**.c" }
        includedirs {"headers","../Memory/headers","../Utils/headers"}
        
        links {"Memory"}

        filter "configurations:Debug" 
            defines { "DEBUG" }  
            symbols "On" 
        
        filter "configurations:Release" 
            defines { "NDEBUG" }      
            optimize "On"

    project "DataStructuresTests"
        kind "ConsoleApp"
        language "C"

        location "build/%{prj.name}"
        targetdir "build/%{prj.name}/bin/%{cfg.buildcfg}"
        objdir "build/%{prj.name}/obj/%{cfg.buildcfg}"

        files { "tests/**.h","tests/**.c" }
        includedirs {"headers","../Memory/headers","../Utils/headers"}
        
        links {"DataStructures"}

        filter "configurations:Debug" 
            defines { "DEBUG" }  
            symbols "On" 
        
        filter "configurations:Release" 
            defines { "NDEBUG" }      
            optimize "On"

    externalproject "Memory"
       location "../Memory"
       uuid "57940020-8E99-AEB6-271F-61E0F7F6B73B"
       kind "StaticLib"
       language "C"

    externalproject "Utils"
       location "../Utils"
       uuid "6f788d01-ed35-4f0b-bbdd-860c7a311d9b"
       kind "StaticLib"
       language "C"