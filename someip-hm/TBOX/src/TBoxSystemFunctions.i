//
// Created by yuzhengyang on 2020/8/8.
//
%module(directors="1")  TBoxSystemFunctions

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
#include "TBoxSystemFunctions.h"
%}

%include "typemaps.i"
%include "various.i"
%include "std_string.i"

%javaconst(1);

%include "public_def.h"

%typemap(jstype)  char * dynamicBYTE "byte[]"
%typemap(jtype)  char * dynamicBYTE "byte[]"
%typemap(jni)  char * dynamicBYTE "jbyteArray"
%typemap(javaout)  char * dynamicBYTE {
        return $jnicall;
}
%typemap(out)  char * dynamicBYTE {
    if($1 != NULL) {
        $result = JCALL1(NewByteArray, jenv, (jsize)arg1->len);
        JCALL4(SetByteArrayRegion, jenv, $result, 0, (jsize)arg1->len, (const jbyte *)$1);
    } else {
        $result = NULL;
    }
}

%typemap(jstype) unsigned int * dynamicIntArray "int[]"
%typemap(jtype)  unsigned int * dynamicIntArray "int[]"
%typemap(jni)  unsigned int * dynamicIntArray "jintArray"
%typemap(javaout) unsigned int * dynamicIntArray {
        return $jnicall;
}
%typemap(out)  unsigned int * dynamicIntArray {
        if($1 != NULL) {
            $result = JCALL1(NewIntArray, jenv, (jsize)arg1->len);
            JCALL4(SetIntArrayRegion, jenv, $result, 0, (jsize)arg1->len, (const jint *)$1);
        } else {
            $result = NULL;
        }
}

%immutable  ConnectionInfo_DT::dynamicBYTE;
%immutable  ConnectionInfo_DT::len;
%immutable  TBoxDTCOut::dynamicIntArray;
%immutable  TBoxDTCOut::len;
%immutable  TBoxAPN2StatusOut::tBoxApn2StatusDt;
%immutable  GPSData_DT::gpsData;

%feature("director") TBoxSystemFuntionsListener;
%include "TBoxSystemFunctions.h"

