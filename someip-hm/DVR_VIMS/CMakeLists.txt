cmake_minimum_required(VERSION 3.4.1)

project (dvr_vims)

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
    dvr_vims
    
    # Sets the library as a shared library.
    SHARED

    # Provides a relative path to your source file(s).
    src/public_util.cpp

    src/DVRSystemConfig.cpp

    src-gen/v1/GREATWALL/DVR_VIMS/DVRSystemConfigSomeIPDeployment.cpp
    src-gen/v1/GREATWALL/DVR_VIMS/DVRSystemConfigSomeIPProxy.cpp
	
    src/DVRStatusReport.cpp

    src-gen/v1/GREATWALL/DVR_VIMS/DVRStatusReportSomeIPDeployment.cpp
    src-gen/v1/GREATWALL/DVR_VIMS/DVRStatusReportSomeIPProxy.cpp

    src/DVRFileOperation.cpp
	
    src-gen/v1/GREATWALL/DVR_VIMS/DVRFileOperationSomeIPDeployment.cpp
    src-gen/v1/GREATWALL/DVR_VIMS/DVRFileOperationSomeIPProxy.cpp

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

target_link_libraries(dvr_vims CommonAPI CommonAPI-SomeIP vsomeip vsomeip3 c++_shared ${log-lib})

install(TARGETS dvr_vims
        LIBRARY DESTINATION .
        )
