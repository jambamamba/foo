#!/bin/bash -xe
set -xe

#after new sd card is booted, you need to run this command first on the board:
#fw_setenv fdt_file imx8mm-var-dart-dt8mcustomboard-m4.dtb && reboot

board=root@192.168.1.64
#ssh $board echo stop > /sys/class/remoteproc/remoteproc0/state

ssh $board rm -f /lib/firmware/rpmsg_lite_str_echo_rtos_imxcm4.elf
scp ~/repos/nextgen/build_wayland/tmp/work/imx8mm_var_dart-fslc-linux/freertos-variscite/2.9.x-r0/git/boards/dart_mx8mm/multicore_examples/rpmsg_lite_str_echo_rtos/armgcc/Debug/rpmsg_lite_str_echo_rtos_imxcm4.elf root@192.168.1.64:/lib/firmware/
ssh $board sync

ssh $board /etc/remoteproc/variscite-rproc-linux -f /lib/firmware/rpmsg_lite_str_echo_rtos_imxcm4.elf
ssh $board cat /sys/class/remoteproc/remoteproc0/state
ssh $board modprobe imx_rpmsg_tty

