workspace "Caffeine" 
    configurations { "Debug","Release" } 
   
    project "Caffeine-Collections"   
        kind "StaticLib"  
        language "C"   
        uuid "fc0b7310-e8ac-4eef-b372-523811590c49"
        
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

    project "Caffeine-Collections-Tests"
        kind "ConsoleApp"
        language "C"
       
        location "build/%{prj.name}"
        targetdir "build/%{prj.name}/bin/%{cfg.buildcfg}"
        objdir "build/%{prj.name}/obj/%{cfg.buildcfg}"

        files { "tests/**.h","tests/**.c" }
        includedirs {"headers","dependencies/Caffeine-Core/headers"}
        
        filter "system:Windows"
           links {"Caffeine-Collections"}

        filter "system:linux"
           links {"Caffeine-Collections","m"}
       

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