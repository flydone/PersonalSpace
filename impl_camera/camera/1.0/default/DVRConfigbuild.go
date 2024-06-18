package DVRConfigbuild  

import (
        "android/soong/android"
         "android/soong/cc"
         "fmt"
)

func init() {
    android.RegisterModuleType("DVR_Config_build", pkiDefaultsFactory)
}

func pkiDefaultsFactory() (android.Module) {
    module := cc.DefaultsFactory()
    android.AddLoadHook(module, AddPkiConfig)
    return module
}

func AddPkiConfig(ctx android.LoadHookContext) {
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
    fmt.Print("DVR kindid profile   GWM_MC01_KINDID  \n")
 if  ctx.Config().Getenv("GWM_MC01_KINDID") == "true"{
        fmt.Print("DVR Kindid profile   config  true \n")
        cppflags = append(cppflags, "-DGWM_MC01_KINDID")
    }
    return cppflags;
}
