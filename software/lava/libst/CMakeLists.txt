# Top level CMake for building the libj1939 library and unit tests
# ----------------------------------------------- Set the minimum CMake version
cmake_minimum_required(VERSION 3.7)


# -------------------------------------------------------- Set the project type
project(st LANGUAGES C CXX ASM)

# ------------------------------------------------------------ Aliases
set(DRIVER_DIR      ${CMAKE_CURRENT_LIST_DIR}/Drivers)

# ------------------------------------------------------------ Get files
file(GLOB_RECURSE SRC_FILES
    ${DRIVER_DIR}/*.c
)

foreach(item ${SRC_FILES})
    if(${item} MATCHES ".*template.c")
            message(STATUS "excluding for Template files: ${item}")
            list(REMOVE_ITEM SRC_FILES ${item})
    endif()
    if(${item} MATCHES ".*Templates.*")
            message(STATUS "excluding for Templates: ${item}")
            list(REMOVE_ITEM SRC_FILES ${item})
    endif()
    if(${item} MATCHES ".*Examples.*")
            message(STATUS "excluding for Templates: ${item}")
            list(REMOVE_ITEM SRC_FILES ${item})
    endif()
endforeach()


#----------------------------------------------------- Define the build target
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

# ----------------------------------------------------------- Set include paths
target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Inc
    PUBLIC ${DRIVER_DIR}/STM32F3xx_HAL_Driver/Inc
    PUBLIC ${DRIVER_DIR}/CMSIS/Include
    PUBLIC ${DRIVER_DIR}/CMSIS/Device/ST/STM32F3xx/Include
)
