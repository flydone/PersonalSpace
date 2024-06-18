cmake_minimum_required(VERSION 2.8)

project (someip-idc_l2)

include_directories(
    src/
    src-gen/
    ../include/
    ../include/CommonAPI-3.1/
    ../include/compat/
)

link_directories(
    $(HARMAN_LIB_DIRS)
)

add_library(someip_idc_l2
	SHARED
    	src/interface.cpp
        src-gen/v1/GREATWALL/IDC_L2_IDC1_5_IDC3_0_MDC_A/IDC_L2SystemFunctionsStubDefault.cpp
        src-gen/v1/GREATWALL/IDC_L2_IDC1_5_IDC3_0_MDC_A/IDC_L2SystemFunctionsSomeIPStubAdapter.cpp
        src-gen/v1/GREATWALL/IDC_L2_IDC1_5_IDC3_0_MDC_A/IDC_L2SystemFunctionsSomeIPProxy.cpp
	src-gen/v1/GREATWALL/IDC_L2_IDC1_5_IDC3_0_MDC_A/IDC_L2SystemFunctionsSomeIPDeployment.cpp

        src-gen/v1/GREATWALL/IDC_L2_IDC1_5_IDC3_0_MDC_A/ADASDisplayInformationSomeIPProxy.cpp
	src-gen/v1/GREATWALL/IDC_L2_IDC1_5_IDC3_0_MDC_A/ADASDisplayInformationSomeIPDeployment.cpp

	src-gen/v1/GREATWALL/MDC_A_IDC3_0/NavigationMapInformationSomeIPProxy.cpp
        src-gen/v1/GREATWALL/MDC_A_IDC3_0/NavigationMapInformationSomeIPDeployment.cpp
        src-gen/v1/GREATWALL/MDC_A_IDC3_0/NavigationMapInformationSomeIPStubAdapter.cpp
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

target_link_libraries(someip_idc_l2  CommonAPI CommonAPI-SomeIP vsomeip vsomeip3 c++_shared ${log-lib})

install(TARGETS someip_idc_l2 
        LIBRARY DESTINATION .
        )

