
workspace "Caffeine" 
    configurations { "Debug","Release" } 
   
    project "Caffeine-Core"   
        kind "StaticLib"  
        language "C"   
        
        targetdir "build/%{prj.name}/bin/%{cfg.buildcfg}"
        objdir "build/%{prj.name}/obj/%{cfg.buildcfg}"
        
        files { "sources/**.h","sources/**.c" }
        includedirs {"headers"}
        
        filter "configurations:Debug" 
            defines { "DEBUG" }  
            symbols "On" 
        
        filter "configurations:Release" 
            defines { "NDEBUG" }      
            optimize "On"