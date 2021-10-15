#!/bin/bash -xe
set -xe

NUM_CORES=$(grep -c processor /proc/cpuinfo)

pushd armgcc
if [ -d "CMakeFiles" ];then rm -rf CMakeFiles; fi
if [ -f "Makefile" ];then rm -f Makefile; fi
if [ -f "cmake_install.cmake" ];then rm -f cmake_install.cmake; fi
if [ -f "CMakeCache.txt" ];then rm -f CMakeCache.txt; fi
popd

PATH_TO_THIS_SCRIPT=$(realpath "$(dirname "$0")")
BUILD_DIR=$PATH_TO_THIS_SCRIPT/../../build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0

CMAKE_MODULE_PATH="$BUILD_DIR/git/middleware/multicore/;"
CMAKE_MODULE_PATH+="$BUILD_DIR/git/rtos/freertos/;"
CMAKE_MODULE_PATH+="$BUILD_DIR/git/devices/MIMX8MM6/drivers/;"
CMAKE_MODULE_PATH+="$BUILD_DIR/git/devices/MIMX8MM6/;"
CMAKE_MODULE_PATH+="$BUILD_DIR/git/CMSIS/Include/;"
CMAKE_MODULE_PATH+="$BUILD_DIR/git/devices/MIMX8MM6/utilities/;"
CMAKE_MODULE_PATH+="$BUILD_DIR/git/components/serial_manager/;"
CMAKE_MODULE_PATH+="$BUILD_DIR/git/components/lists/;"
CMAKE_MODULE_PATH+="$BUILD_DIR/git/components/uart/;"

export CMAKE_MODULE_PATH=$CMAKE_MODULE_PATH
export ARMGCC_DIR=$BUILD_DIR/gcc-arm-none-eabi-9-2020-q2-update/
export CMAKE_TOOLCHAIN_FILE=$BUILD_DIR/git/tools/cmake_toolchain_files/armgcc.cmake

mkdir -p armgcc/build
pushd armgcc/build

rm -fr *
cmake -DCMAKE_MODULE_PATH=$CMAKE_MODULE_PATH -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ..
make -j$NUM_CORES

popd
