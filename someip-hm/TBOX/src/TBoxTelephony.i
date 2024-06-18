//
// Created by yuzhengyang on 2020/8/4.
//
%module(directors="1")  TBoxTelephony

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
#include "TBoxTelephony.h"
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

%typemap(out)  char * dynamicBYTE (jbyte js) {
        if($1 != NULL) {
            $result = JCALL1(NewByteArray, jenv, (jsize)arg1->len);
            JCALL4(SetByteArrayRegion, jenv, $result, 0, (jsize)arg1->len, (const jbyte *)$1);
        } else {
            $result = NULL;
        }
}

%typemap(in)     (char * buf, size_t size) {
    $1 = (char *) JCALL2(GetByteArrayElements, jenv, $input, 0);
    $2 = (size_t) JCALL1(GetArrayLength, jenv, $input);
}
%typemap(jni)    (char * buf, size_t size) "jbyteArray"
%typemap(jtype)  (char * buf, size_t size) "byte[]"
%typemap(jstype) (char * buf, size_t size) "byte[]"
%typemap(javain) (char * buf, size_t size) "$javainput"


%immutable  TBoxTelephoneNumber_DT::dynamicBYTE;
%ignore TBoxTelephoneNumber_DT::len;
%ignore TEL_NUM_LEN;
%feature("director") TBoxTelephonyListener;
%include "TBoxTelephony.h"
