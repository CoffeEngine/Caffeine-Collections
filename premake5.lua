workspace "Caffeine" 
    configurations { "Debug","Release" } 
    location "build"

    project "DataStructures"   
        kind "None"  
        language "C"   
        
        location "build/%{prj.name}"
        targetdir "build/%{prj.name}/bin/%{cfg.buildcfg}"
        objdir "build/%{prj.name}/obj/%{cfg.buildcfg}"
        
        files { "src/**.h","includes/*h" }
        includedirs {"includes"}
        
        filter "configurations:Debug" 
            defines { "DEBUG" }  
            symbols "On" 
        
        filter "configurations:Release" 
            defines { "NDEBUG" }      
            optimize "On" 
    
    project "NGE_Example"   
        kind "ConsoleApp"  
        language "C"

        location "build/%{prj.name}"
        targetdir "build/%{prj.name}/bin/%{cfg.buildcfg}"
        objdir "build/%{prj.name}/obj/%{cfg.buildcfg}"

        files {"examples/nge/src/*.h", "examples/nge/src/*.c" }
       includedirs {"includes"}

        filter "configurations:Debug" 
            defines { "DEBUG" }  
            symbols "On" 
        
        filter "configurations:Release" 
            defines { "NDEBUG" }      
            optimize "On" 

    project "Testes"   
        kind "ConsoleApp"  
        language "C"

        location "build/%{prj.name}"
        targetdir "build/%{prj.name}/bin/%{cfg.buildcfg}"
        objdir "build/%{prj.name}/obj/%{cfg.buildcfg}"

        files {"test/*.h", "test/*.c" }
        includedirs {"includes"}

        filter "configurations:Debug" 
            defines { "DEBUG" }  
            symbols "On" 
        
        filter "configurations:Release" 
            defines { "NDEBUG" }      
            optimize "On" 