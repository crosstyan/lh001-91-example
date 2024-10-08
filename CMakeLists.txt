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

add_subdirectory(components)
