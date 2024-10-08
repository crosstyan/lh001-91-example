# CMSIS & standard peripheral library & startup files
file(GLOB MCU_LIB_SRCS mcu/gd32f330/lib/src/*.c)
set(MCU_LIB_INC_DIR mcu/gd32f330/lib/inc)
set(MCU_LIB_CMSIS_INC_DIR mcu/gd32f330/CMSIS/Core/Include)
set(MCU_LIB_OPT_INC_DIR mcu/gd32f330/inc)

add_library(mcu_lib ${MCU_LIB_SRCS})
target_sources(mcu_lib PRIVATE mcu/gd32f330/startup_gd32f3x0.S)
target_include_directories(mcu_lib PUBLIC 
    ${MCU_LIB_INC_DIR} 
    ${MCU_LIB_CMSIS_INC_DIR}
    ${MCU_LIB_OPT_INC_DIR})

# LH001-91 library and port SPI driver
file(GLOB MCU_LIB_PORT_SRCS mcu/gd32f330/port/*.c)
set(MCU_LIB_PORT_INC_DIR mcu/gd32f330/port)
add_library(lh_lib lh_lib/LH001_91.c ${MCU_LIB_PORT_SRCS})
target_include_directories(lh_lib PUBLIC lh_lib ${MCU_LIB_PORT_INC_DIR})
target_link_libraries(lh_lib mcu_lib)
