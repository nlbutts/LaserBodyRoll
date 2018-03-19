# ------------------------------------------------------- MINIMUM CMAKE VERSION
cmake_minimum_required(VERSION 3.4)

# ---------------------------------------------------------------- PROJECT NAME
set(LOCAL_PROJ_NAME vl53l0x)

# -------------------------------------------------------------- FIND SRC FILES
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_LIST_DIR}/Api/*.c
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)



# Analogs.cpp
# CAN.cpp
# ClockControl.cpp
# ClockControl.cpp.orig
# CRCHw.cpp
# CriticalSection.cpp
# DigitalToAnalog.cpp
# DMA.cpp
# FlashInfo.cpp
# FlashProgram.cpp
# FSMC.cpp
# GPIO.cpp
# GPIOInterrupt.cpp
# GPIOMuxPin.cpp
# I2C.cpp
# I2SClock.cpp
# I2SClock.cpp.orig
# IndependentWatchdog.cpp
# Interrupt.cpp
# PDMReceiverMaster.cpp
# PeriodicInterruptTimer.cpp
# PWM.cpp
# ResetControl.cpp
# ResetControl.cpp.orig
# RNG.cpp
# SPI.cpp
# SysTickTimer.cpp
# Timer.cpp
# UART.cpp
# UartInterrupt.cpp


# ----------------------------------------- FILE EXCLUSION FOR WINDOWS PLATFORM
foreach(item ${SRC_FILES})
    if(${item} MATCHES "vl53l0x_i2c_win_serial_comms.c"
        OR ${item} MATCHES vl53l0x_platform_log.c)
            message(STATUS "excluding legacy: ${item}")
            list(REMOVE_ITEM SRC_FILES ${item})
    endif()
endforeach()

# --------------------------------------------- FILE EXCLUSION FOR X86/UT BUILD
if(NOT ${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm_baremetal")
    foreach(item ${SRC_FILES})
        if(${item} MATCHES ".*micro.*\.cpp"
            OR ${item} MATCHES ".*device.*\.cpp"
            OR ${item} MATCHES ".*debug.*\.cpp"
            OR ${item} MATCHES ".*NVSection\.cpp"
            OR ${item} MATCHES ".*JEDEC\.cpp"
            OR ${item} MATCHES ".*Button\.cpp")
            message(STATUS "excluding from build: ${item}")
            list(REMOVE_ITEM SRC_FILES ${item})
        endif()
    endforeach()
endif()

# --------------------------------------------------------- DEFINE BUILD TARGET
add_library(${LOCAL_PROJ_NAME} STATIC ${SRC_FILES})

target_link_libraries(${LOCAL_PROJ_NAME} PUBLIC st embedded)

# -------------------------------------------------------------- FIND SRC FILES
target_include_directories(${LOCAL_PROJ_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Api/core/inc)
target_include_directories(${LOCAL_PROJ_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Api/platform/inc)
target_include_directories(${LOCAL_PROJ_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
