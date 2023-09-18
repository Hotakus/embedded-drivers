cmake_minimum_required(VERSION 3.20)
project(hello C)

set(CMAKE_C_STANDARD 99)

set(LINUX_KERNEL_DIR /home/hotakus/workspace/drivers/100ask_imx6ull_mini-sdk/Buildroot_2020.02.x/output/build/linux-origin_master/)
#set(LINUX_KERNEL_DIR /home/hotakus/workspace/drivers/100ask_imx6ull_mini-sdk/Linux-4.9.88/)

add_definitions(-D__KERNEL__)

include_directories(
        .
        ../include/
        ${LINUX_KERNEL_DIR}include/
        ${LINUX_KERNEL_DIR}arch/arm/include/
        # ${LINUX_KERNEL_DIR}include/asm-generic/
)

add_executable(hello hello.c)
