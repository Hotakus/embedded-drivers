cmake_minimum_required(VERSION 3.20)
project(hello C)
set(CMAKE_C_STANDARD 99)

set(LINUX_KERNEL_DIR /home/hotakus/workspace/drivers/100ask_imx6ull_mini-sdk/Buildroot_2020.02.x/output/build/linux-origin_master/)
add_definitions(-D__KERNEL__)

include_directories(
        .
        ../common_inc/
        ../../../include/imx6ull/
        ${LINUX_KERNEL_DIR}include/
        ${LINUX_KERNEL_DIR}arch/arm/include/
)

add_executable(hello
        hello.c
        hello_handle.c
)