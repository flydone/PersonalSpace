#ifndef _interface_HPP_
#define _interface_HPP_
#include "listener.hpp"
#include "ADASDisplayInformation.hpp"
#include "NavigationMapInformation.hpp"

#include <CommonAPI/CommonAPI.hpp>
#include <android/log.h>
#include <sys/system_properties.h>
#include <iostream>
#include <string>
#include <unistd.h>
#define LOG_TAG "IDC_L2_SOMEIP_TAG"
#define DLL_PUBLIC __attribute__((visibility("default")))
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
void listener_init_(char *appName, char *configFile);
bool listenerIsReady();
void setListener_(Listener *listener);

bool ADASDisplayInformationIsReady();
void ADASDisplayInformationInit(char *appName, char *configFile);
void ADASDisplayInformationListenerRegister(ADASDisplayInformationListener *listener);

void navigationMap_init(char *appName, char *configFile);
bool navigationMapIsReady();
CallStatus_DT navPathInfoReq(const char *_SDRoute);
#endif
