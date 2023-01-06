workspace "Caffeine" 
    configurations { "Debug","Release" } 
   
    project "DataStructures"   
        kind "StaticLib"  
        language "C"   
        
        targetdir "build/%{prj.name}/bin/%{cfg.buildcfg}"
        objdir "build/%{prj.name}/obj/%{cfg.buildcfg}"
        
        files { "sources/**.h","sources/**.c","dependencies/Caffeine-Core/sources/**.c" }
        includedirs {"headers","dependencies/Caffeine-Core/headers"}
        
      
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
        includedirs {"headers","dependencies/Caffeine-Core/headers"}
        
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
       location "dependencies/Caffeine-Core"
       kind "StaticLib"
       language "C"