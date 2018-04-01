# ------------------------------------------------------- MINIMUM CMAKE VERSION
cmake_minimum_required(VERSION 3.4)

# ---------------------------------------------------------------- PROJECT NAME
set(LOCAL_PROJ_NAME embedded)

# -------------------------------------------------------------- FIND SRC FILES
# file(GLOB_RECURSE SRC_FILES
#     ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
#     ${CMAKE_CURRENT_LIST_DIR}/src/*.c)
set(SRC_FILES src/embedded/micro/stm32/Timer.cpp
              src/embedded/micro/stm32/GPIO.cpp
              src/embedded/micro/stm32/DigitalToAnalog.cpp
              src/embedded/memory/winbond/NORFlash.cpp
              src/embedded/micro/stm32/SPIInterface.cpp
              src/embedded/memory/NVSection.cpp)

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


# --------------------------------------------- FILE EXCLUSION FOR STM32F405
foreach(item ${SRC_FILES})
    if(${item} MATCHES "FSMC.cpp")
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
            OR ${item} MATCHES ".*JEDEC\.cpp"
            OR ${item} MATCHES ".*Button\.cpp")
            message(STATUS "excluding from build: ${item}")
            list(REMOVE_ITEM SRC_FILES ${item})
        endif()
    endforeach()
endif()

# --------------------------------------------------------- DEFINE BUILD TARGET
add_library(${LOCAL_PROJ_NAME} STATIC ${SRC_FILES})

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm_baremetal")
    target_link_libraries(${LOCAL_PROJ_NAME} PUBLIC st)
endif()

# -------------------------------------------------------------- FIND SRC FILES
target_include_directories(${LOCAL_PROJ_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
