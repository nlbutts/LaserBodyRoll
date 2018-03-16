# Top level CMake for building the libj1939 library and unit tests
# ----------------------------------------------- Set the minimum CMake version
cmake_minimum_required(VERSION 3.7)


# -------------------------------------------------------- Set the project type
project(application LANGUAGES C CXX ASM)


# ---------------------------------------------------------- ONLY BUILD FOR ARM
if(NOT ${CMAKE_SYSTEM_PROCESSOR} MATCHES arm_baremetal)
    message(FATAL_ERROR "Application can only be built for arm_baremetal!")
endif()


# --------------------------------------------------------------- PROJECT NAMES
set(THIS_RELEASE application.elf)
set(THIS_DEBUG application_debug.elf)


# -------------------------------------------------------------- FIND SRC FILES
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/*.c
    ${CMAKE_CURRENT_LIST_DIR}/src/*.S
)

file(GLOB_RECURSE SYSTEM_FILES
    ${CMAKE_SOURCE_DIR}/system/src/*.cpp
    ${CMAKE_SOURCE_DIR}/system/src/*.c
    ${CMAKE_SOURCE_DIR}/system/src/*.S
)


# -------------------------------------------------------------- PRINT THE SIZE
add_custom_target(RELEASE_APP_SIZE ALL 
                  COMMAND ${CROSS_SZ} ${CMAKE_CURRENT_BINARY_DIR}/${THIS_RELEASE}
                  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${THIS_RELEASE})
add_custom_target(DEBUG_APP_SIZE ALL 
                  COMMAND ${CROSS_SZ} ${CMAKE_CURRENT_BINARY_DIR}/${THIS_DEBUG}
                  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${THIS_DEBUG})


# --------------------------------------------------------- DEFINE BUILD TARGET
set(THIS_LINK_LIBS st embedded)
add_executable(${THIS_RELEASE} ${SRC_FILES} ${SYSTEM_FILES})
target_link_libraries(${THIS_RELEASE} ${THIS_LINK_LIBS})

add_executable(${THIS_DEBUG} ${SRC_FILES} ${SYSTEM_FILES})
target_link_libraries(${THIS_DEBUG} ${THIS_LINK_LIBS})


# ------------------------------------------------------------- INCLUDE FOLDERS
target_include_directories(${THIS_RELEASE}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include
)

target_include_directories(${THIS_DEBUG}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include
)


# ----------------------------------------------------------- SET LINKER SCRIPT
set(LDSCRIPTS_PATH ${CMAKE_CURRENT_LIST_DIR}/../ldscripts)

target_link_libraries(${THIS_RELEASE}
    "-T ${LDSCRIPTS_PATH}/Application_release.ld -L${LDSCRIPTS_PATH}"
)

target_link_libraries(${THIS_DEBUG}
    "-T ${LDSCRIPTS_PATH}/Application_debug.ld -L${LDSCRIPTS_PATH}"
)


# ---------------------------------------------------------------- SET MAP FILE
target_link_libraries(${THIS_RELEASE}
    "-Xlinker -Map=${CMAKE_CURRENT_BINARY_DIR}/${THIS_RELEASE}.map"
)

target_link_libraries(${THIS_DEBUG}
    "-Xlinker -Map=${CMAKE_CURRENT_BINARY_DIR}/${THIS_DEBUG}.map"
)


# ----------------------------------------------------- ADD VERSION INFORMATION
# set_property(
#     SOURCE ${CMAKE_CURRENT_LIST_DIR}/src/application/FirmwareVersion.cpp
#     APPEND PROPERTY COMPILE_DEFINITIONS
#         SMART_NOZZLE_APP_PN=\"${SMART_NOZZLE_APP_PN}\"
#         SMART_NOZZLE_BUILD_VERSION=\"${SMART_NOZZLE_BUILD_VERSION}\"
#         SMART_NOZZLE_BUILD_DATE=\"${SMART_NOZZLE_BUILD_DATE}\"
#         SMART_NOZZLE_VCS_HASH=\"${SMART_NOZZLE_VCS_HASH}\"
# )


# -------------------------------------------------------------- INSTALL TARGET
# The buildserver.sh script (and Jenkins) will depend on these files

set(INSTALL_BASENAME "application")

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${THIS_RELEASE}
        RENAME ${INSTALL_BASENAME}.elf
        DESTINATION ./
)
