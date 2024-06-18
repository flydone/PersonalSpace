#======================================================================
#makefile for someip file providing by gwm
#======================================================================
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE        := init.gwm.someip.rc
LOCAL_MODULE_OWNER  := GWM
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := init.gwm.someip.rc
ifeq ($(shell expr $(PLATFORM_VERSION) \> 10), 1)
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/init
else
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/vendor/etc/init
endif
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := ETS_Client_UDP.json
LOCAL_MODULE_OWNER  := GWM
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ets_deliver/config/ETS_Client_UDP.json
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/vendor/etc/someip
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := ETS_Service_UDP.json
LOCAL_MODULE_OWNER  := GWM
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ets_deliver/config/ETS_Service_UDP.json
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/vendor/etc/someip
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := etsclient
LOCAL_MODULE_OWNER  := GWM
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ./ets_deliver/bin/etsclient
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/vendor/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := etsserver
LOCAL_MODULE_OWNER  := GWM
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ./ets_deliver/bin/etsserver
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/vendor/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := run_ets.sh
LOCAL_MODULE_OWNER  := GWM
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ./ets_deliver/run_ets.sh
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/vendor/bin
include $(BUILD_PREBUILT)

