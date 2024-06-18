cmake_minimum_required(VERSION 3.4.1)

project (someip_avp)

include_directories(
    src-gen/
    ../include/
    ../include/CommonAPI-3.1/
    ../include/compat/
)

link_directories(
    $(HARMAN_LIB_DIRS)
)

add_library(
    # Specifies the name of the library.
    someip_hap
    
    # Sets the library as a shared library.
    SHARED

    # Provides a relative path to your source file(s).
    src/public_util.cpp
    src/HAVPSystemFunctions.cpp

    src-gen/v1/GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP/HAVPandAVPFunctionsStubDefault.cpp
    src-gen/v1/GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP/HAVPandAVPFunctionsSomeIPStubAdapter.cpp
    
    src-gen/v1/GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP/HAVPandAVPFunctionsSomeIPProxy.cpp
    src-gen/v1/GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP/HAVPandAVPFunctionsSomeIPDeployment.cpp

)

add_library( CommonAPI
        SHARED
        IMPORTED )

set_target_properties( CommonAPI
        PROPERTIES IMPORTED_LOCATION
        ${HARMAN_LIB_DIRS}/libCommonAPI.so )

add_library( CommonAPI-SomeIP
        SHARED
        IMPORTED )
set_target_properties( CommonAPI-SomeIP
        PROPERTIES IMPORTED_LOCATION
        ${HARMAN_LIB_DIRS}/libCommonAPI-SomeIP.so )

add_library( vsomeip
        SHARED
        IMPORTED )
set_target_properties( vsomeip
        PROPERTIES IMPORTED_LOCATION
        ${HARMAN_LIB_DIRS}/libvsomeip.so )

add_library( vsomeip3
        SHARED
        IMPORTED )
set_target_properties( vsomeip3
        PROPERTIES IMPORTED_LOCATION
        ${HARMAN_LIB_DIRS}/libvsomeip3.so )

find_library(
        log-lib
        log)

target_link_libraries(someip_hap CommonAPI CommonAPI-SomeIP vsomeip vsomeip3 c++_shared ${log-lib})

install(TARGETS someip_hap
        LIBRARY DESTINATION .
        )
