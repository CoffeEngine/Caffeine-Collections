workspace "Caffeine" 
    configurations { "Debug","Release" } 
   
    project "DataStructures"   
        kind "StaticLib"  
        language "C"   
        
        targetdir "build/%{prj.name}/bin/%{cfg.buildcfg}"
        objdir "build/%{prj.name}/obj/%{cfg.buildcfg}"
        
        files { "sources/**.h","sources/**.c","../Caffeine-Core/sources/**.c" }
        includedirs {"headers","../Caffeine-Core/headers"}
        
      
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
        includedirs {"headers","../Caffeine-Core/headers"}
        
        filter "system:Windows"
           links {"DataStructures"}

        filter "system:linux"
           links {"DataStructures","m"}
       

        filter "configurations:Debug" 
            defines { "DEBUG" }  
            symbols "On" 
        
        filter "configurations:Release" 
            defines { "NDEBUG" }      
            optimize "On"

    externalproject "Caffeine-Core"
       location "../Caffeine-Core"
       uuid "6f788d01-ed35-4f0b-bbdd-860c7a311d9b"
       kind "StaticLib"
       language "C"