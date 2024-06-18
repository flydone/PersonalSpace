#!/bin/bash

PLATFORM=arm64-v8a
BUILDTYPE=Debug

#source ../../build-common.sh

#COMMUNICATION_MATRIX=./excel2fidl/GWM_V3.5_Platform_SOMEIP_Static_InterfaceDescription_V1.1.xlsx
#COMMUNICATION_MATRIX=./excel2fidl/GWM_V3.5_Platform_SOMEIP_Static_InterfaceDescription_V1.5_HUT_Only.xlsx
#COMMUNICATION_MATRIX=./excel2fidl/GWM_GEEP_Platform_SOMEIP_Static_InterfaceDescription_V2.2.xlsx
#COMMUNICATION_MATRIX=./excel2fidl/GWM_GEEP_Platform_SOMEIP_Static_InterfaceDescription_V2.5_DVR_VIMS.xlsx
#COMMUNICATION_MATRIX=./excel2fidl/GWM_GEEP_Platform_SOMEIP_Static_InterfaceDescription_V2.6.1.xlsx
#COMMUNICATION_MATRIX=./excel2fidl/GWM_GEEP_Platform_SOMEIP_Static_InterfaceDescription_V2.8.1_DVR_VIMS.xlsx
COMMUNICATION_MATRIX=./excel2fidl/GWM_GEEP_Platform_SOMEIP_Static_InterfaceDescription_V3.0_IDC_3.0.xlsx
clean(){
  rm -rf ./fidl
  rm -rf ./src-gen
  rm -rf ./build
}


xlsx2fidl(){
  ./excel2fidl/NewBean-excel2fidl ${COMMUNICATION_MATRIX} ./fidl
  #./excel2fidl/linux_fidl_tool ${COMMUNICATION_MATRIX} ./fidl
}

fidl2cpp(){
  toolpath=./tools
  fidlpath=./fidl/
  for file in `ls ${fidlpath}`
  do
    suffix=${file##*.}
    if [ "${suffix}"x = "fdepl"x ]; then
       fdepl_file=${fidlpath}$file
       fidl_file=${fidlpath}${file%.*}.fidl
       echo ${fdepl_file}
       echo ${fidl_file}
       ${toolpath}/commonapi-generator/commonapi-generator-linux-x86_64 --dest ./src-gen --skel ${fidl_file}
       ${toolpath}/commonapi-generator/commonapi-generator-linux-x86_64 --dest ./src-gen ${fdepl_file}
       ${toolpath}/commonapi_someip_generator/commonapi-someip-generator-linux-x86_64 --dest ./src-gen ${fdepl_file}
    fi
  done
}
#clean
xlsx2fidl
fidl2cpp


