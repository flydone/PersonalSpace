/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

#ifndef SWIG_TBoxTelephony_WRAP_H_
#define SWIG_TBoxTelephony_WRAP_H_

class SwigDirector_TBoxTelephonyListener : public TBoxTelephonyListener, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_TBoxTelephonyListener(JNIEnv *jenv);
    virtual ~SwigDirector_TBoxTelephonyListener();
    virtual void TBoxSimStatusChangedListener(TBoxSimStatusStruct_DT tBoxSimStatusStructDt);
    virtual void TBoxNetworkProviderChangedListener(TBoxNetworkProviderStruct_DT tBoxNetworkProviderStructDt);
    virtual void TBoxSignalStrengthChangedListener(TBoxSignalStrengthStruct_DT tBoxSignalStrengthStructDt);
    virtual void TBoxCallStateEventListener(TBoxCallStateEvent_DT event);
public:
    bool swig_overrides(int n) {
      return (n < 4 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<4> swig_override;
};


#endif