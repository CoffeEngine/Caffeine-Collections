workspace "Caffeine" 
    configurations { "Debug","Release" } 
    location "build"

    project "DataStructures"   
        kind "None"  
        language "C"   
        
        location "build/%{prj.name}"
        targetdir "build/%{prj.name}/bin/%{cfg.buildcfg}"
        objdir "build/%{prj.name}/obj/%{cfg.buildcfg}"
        
        files { "src/**.h","src/**.c","includes/*h" }
        includedirs {"includes"}
        
        filter "configurations:Debug" 
            defines { "DEBUG" }  
            symbols "On" 
        
        filter "configurations:Release" 
            defines { "NDEBUG" }      
            optimize "On"