#!/bin/bash

PLATFORM=arm64-v8a
BUILDTYPE=Debug

export ANDROID_NDK_ROOT="~/Android/Sdk/ndk/android-ndk-r20b"
#NDKPATH=./tools/android-ndk-r20
NDKPATH=${ANDROID_NDK_ROOT}

# FIXME
BASEPATH=$(pwd)/..

CXXFLAGS="-std=c++11 -frtti -fPIC -v -fexceptions "

HARMAN_LIB_D=${BASEPATH}/libs/${PLATFORM}
INSTALL_LIB_D=${BASEPATH}/libs/${PLATFORM}

CMAKE="cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_TOOLCHAIN_FILE=${NDKPATH}/build/cmake/android.toolchain.cmake -DANDROID_ABI=${PLATFORM} -DANDROID_NDK=${NDKPATH} -DANDROID_NATIVE_API_LEVEL=android-28 "

