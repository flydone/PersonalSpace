//
// Created by yuzhengyang on 2020/8/5.
//
%module(directors="1")  TBoxTSPCom

%pragma(java) jniclasscode=%{
    static {
        try {
            System.loadLibrary("tbox_client");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load. \n" + e);
            System.exit(1);
        }
    }
%}

%{
#include "TBoxTSPCom.h"
%}

%include "typemaps.i"
%include "various.i"
%include "std_string.i"
%javaconst(1);

%include "public_def.h"

%feature("director") TBoxTSPComListener;
%include "TBoxTSPCom.h"
