package HealthConfigbuild  

import (
        "android/soong/android"
         "android/soong/cc"
         "fmt"
)

func init() {
    android.RegisterModuleType("Health_Config_build", healthDefaultsFactory)
}

func healthDefaultsFactory() (android.Module) {
    module := cc.DefaultsFactory()
    android.AddLoadHook(module, AddHealthConfig)
    return module
}

func AddHealthConfig(ctx android.LoadHookContext) {
    type props struct {
        Shared_libs []string
        Cflags []string
    }
    p := &props{}
  
    p.Cflags = addFlags(ctx)
    ctx.AppendProperties(p)
}


func addFlags(ctx android.BaseContext) ([]string) {
    var cppflags []string
    if ctx.Config().Getenv("GWM_V4") == "true"{
        fmt.Print("Health GWM_V4 config  true \n")
        cppflags = append(cppflags, "-DGWM_V4")
    }

    if ctx.Config().Getenv("GWM_V4_DV") == "true"{
        fmt.Print("Health GWM_V4_DV config  true \n")
        cppflags = append(cppflags, "-DGWM_V4_DV")
    }
    return cppflags;
}
