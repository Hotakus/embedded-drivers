cmake_minimum_required(VERSION 3.20)
project(hello_module C)
set(CMAKE_C_STANDARD 99)

add_definitions(-D__KERNEL__)
set(LINUX_KERNEL_DIR /home/hotakus/workspace/drivers/100ask_imx6ull_mini-sdk/Buildroot_2020.02.x/output/build/linux-origin_master/)
set(CMAKE_C_COMPILER /home/hotakus/workspace/drivers/100ask_imx6ull_mini-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin/arm-buildroot-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER /home/hotakus/workspace/drivers/100ask_imx6ull_mini-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin/arm-buildroot-linux-gnueabihf-g++)

include_directories(
        .
        ../../include/imx6ull/
        ${LINUX_KERNEL_DIR}include/
        ${LINUX_KERNEL_DIR}arch/arm/include/
)

aux_source_directory(
        ./app
        SRC_DIR
)

add_executable(hello.exe ${SRC_DIR})
