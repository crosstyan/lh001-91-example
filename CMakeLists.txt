cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE
        ${CMAKE_CURRENT_LIST_DIR}/toolchain-arm-none-eabi.cmake)

project(lh001-91-example)
enable_language(ASM)
enable_language(C)
enable_language(CXX)

set(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(-DGD32F330)
add_subdirectory(components)
add_executable(lh001
        src/main.c)
# https://community.platformio.org/t/stm32f030r8t6-pcb-with-gd32f330r8t6-variant/33494/3
#
# https://github.com/CommunityGD32Cores/ArduinoCore-GD32
# linker script
# https://github.com/CommunityGD32Cores/ArduinoCore-GD32/blob/main/variants/GD32F330CB_GENERIC/ldscript.ld
# https://github.com/CommunityGD32Cores/ArduinoCore-GD32/tree/main/variants/GD32F330CB_GENERIC
# startup file
# https://github.com/CommunityGD32Cores/ArduinoCore-GD32/blob/main/system/startup/startup_gd32f3x0.S
set(LD_SCRIPT_PATH ${CMAKE_CURRENT_LIST_DIR}/ldscript.ld)
get_filename_component(LD_SCRIPT_PATH_ABSOLUTE ${LD_SCRIPT_PATH} ABSOLUTE)
set_target_properties(lh001 PROPERTIES
        SUFFIX ".elf"
        LINK_DEPENDS ${LD_SCRIPT_PATH_ABSOLUTE}
        LINK_FLAGS "-T \"${LD_SCRIPT_PATH_ABSOLUTE}\" \
                    -Wl,-Map=\"${CMAKE_CURRENT_BINARY_DIR}/${target}.map\"")
target_link_libraries(lh001 PRIVATE lh_lib)

