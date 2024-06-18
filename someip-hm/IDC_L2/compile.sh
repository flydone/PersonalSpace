source ../build_common.sh

if [ $# -eq 0 ]; then
    BUILDTYPE=Debug
fi

if [ "$1" = "Release" ]; then
    BUILDTYPE=Release
fi

compile(){
  rm -rf ./build
  mkdir build
  cd build
  ${CMAKE} -DCMAKE_BUILD_TYPE=${BUILDTYPE}	\
	-DCMAKE_CXX_FLAGS=${CXXFLAGS}	\
	-DCMAKE_INSTALL_PREFIX=${INSTALL_LIB_D}	\
	-DHARMAN_LIB_DIRS=${HARMAN_LIB_D}	\
    ..
  make
  make install
  rm -rf ../build
}

compile