#ARMGCC_DIR=/home/oosman/repos/nextgen/build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/gcc-arm-none-eabi-9-2020-q2-update/ cmake -DCMAKE_TOOLCHAIN_FILE=/home/oosman/repos/nextgen/build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/tools/cmake_toolchain_files/armgcc.cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" .

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE})

# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.1.1)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
SET(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})


project(rpmsg_lite_str_echo_rtos_imxcm4)

set(MCUX_SDK_PROJECT_NAME rpmsg_lite_str_echo_rtos_imxcm4.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../main_remote.c"
"${ProjDirPath}/../FreeRTOSConfig.h"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../rpmsg_config.h"
"${ProjDirPath}/../rsc_table.c"
"${ProjDirPath}/../rsc_table.h"
"${ProjDirPath}/../remoteproc.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../fsl_iomuxc.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/boards/dart_mx8mm/multicore_examples/rpmsg_lite_str_echo_rtos/armgcc/..
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/boards/dart_mx8mm/multicore_examples/rpmsg_lite_str_echo_rtos/armgcc/debug
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/middleware/multicore/rpmsg_lite/lib/include/platform/imx8mm_m4
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/middleware/multicore/rpmsg_lite/lib/include
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/rtos/freertos/freertos_kernel/include
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/rtos/freertos/freertos_kernel/portable/GCC/ARM_CM4F
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/devices/MIMX8MM6/drivers/.
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/devices/MIMX8MM6/.
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/CMSIS/Include/.
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/devices/MIMX8MM6/utilities/str
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/devices/MIMX8MM6/utilities/debug_console
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/components/serial_manager/.
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/components/uart/.
    ${ProjDirPath}/../../../../../imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/components/lists/.
)

set(CMAKE_MODULE_PATH
    /home/oosman/repos/nextgen/build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/devices/MIMX8MM6
    /home/oosman/repos/nextgen/build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/middleware/multicore
    /home/oosman/repos/nextgen/build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/middleware/multicore
    /home/oosman/repos/nextgen/build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/devices/MIMX8MM6/utilities
    /home/oosman/repos/nextgen/build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/CMSIS/Include
    /home/oosman/repos/nextgen/build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/rtos/freertos/
    /home/oosman/repos/nextgen/build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/devices/MIMX8MM6/drivers/
    /home/oosman/repos/nextgen/build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/components/serial_manager/
    /home/oosman/repos/nextgen/build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/components/lists/
    /home/oosman/repos/nextgen/build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/components/uart/
    )
message("################ CMAKE_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE} ###################")
message("################ ProjDirPath ${ProjDirPath} ###################")
message("################ CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ###################")

SET(CMAKE_MODULE_PATH "$CMAKE_MODULE_PATH;$ENV{CMAKE_MODULE_PATH}")

# include modules

include(middleware_multicore_rpmsg_lite_imx8mm_m4_freertos_MIMX8MM6)

include(middleware_freertos-kernel_heap_4_MIMX8MM6)

include(driver_clock_MIMX8MM6)

include(driver_mu_MIMX8MM6)

include(middleware_freertos-kernel_MIMX8MM6)

include(driver_common_MIMX8MM6)

include(driver_rdc_MIMX8MM6)

include(device_MIMX8MM6_CMSIS_MIMX8MM6)

include(utility_debug_console_MIMX8MM6)

include(component_iuart_adapter_MIMX8MM6)

include(component_serial_manager_MIMX8MM6)

include(component_lists_MIMX8MM6)

include(component_serial_manager_uart_MIMX8MM6)

include(driver_iuart_MIMX8MM6)

include(device_MIMX8MM6_startup_MIMX8MM6)

include(utility_assert_MIMX8MM6)

include(middleware_multicore_rpmsg_lite_MIMX8MM6)

include(middleware_freertos-kernel_extension_MIMX8MM6)

include(CMSIS_Include_core_cm4_MIMX8MM6)

include(CMSIS_Include_common_MIMX8MM6)

include(CMSIS_Include_dsp_MIMX8MM6)

include(utilities_misc_utilities_MIMX8MM6)

include(device_MIMX8MM6_system_MIMX8MM6)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/rpmsg_lite_str_echo_rtos.bin)

