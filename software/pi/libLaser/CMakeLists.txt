cmake_minimum_required (VERSION 3.5)
project (laser)

SET(CMAKE_C_FLAGS "-O0 -std=c11 -g3")
SET(CMAKE_CXX_FLAGS "-O0 -std=c++11 -g3")


add_subdirectory(libVL53L0X)

#add_custom_command(OUTPUT laser.so DEPENDS ${PROJECT_SOURCE_DIR}/liblaser.so COMMAND cp liblaser.so laser.so )
#add_custom_target(laser.so ALL DEPENDS laser.so COMMAND cp liblaser.so laser.so)

add_library(${PROJECT_NAME} STATIC src/libentry.cpp src/vl53l0x_i2c_platform.c ${CSRC})

target_link_libraries(${PROJECT_NAME} VL53L0X)

include_directories(${PROJECT_SOURCE_DIR}/libVL53L0X/core/inc)
include_directories(${PROJECT_SOURCE_DIR}/libVL53L0X/platform/inc)
#include_directories(${PYTHON_INCLUDE_PATH})
#include_directories(/usr/include/python3.4m)

