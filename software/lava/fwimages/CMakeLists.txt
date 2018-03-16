# ------------------------------------------------------- MINIMUM CMAKE VERSION
cmake_minimum_required(VERSION 3.4)


# ---------------------------------------------------------- ONLY BUILD FOR ARM
if(NOT ${CMAKE_SYSTEM_PROCESSOR} MATCHES arm_baremetal)
    message(FATAL_ERROR "${CMAKE_CURRENT_LIST_FILE} can only be built for arm_baremetal!")
endif()


# ----------------------------------------------------- BUILD APPLICATION FILES
# Built in application/CMakeLists.txt
set(APPLICATION_ELF application.elf)

# Built locally
set(APPLICATION_HEX application.hex)
set(APPLICATION_CRC_HEX application_crc.hex)
set(APPLICATION_CRC_BIN application_crc.bin)

add_custom_command(
    OUTPUT ${APPLICATION_HEX}
    COMMAND ${OC} -O ihex $<TARGET_FILE:${APPLICATION_ELF}> ${APPLICATION_HEX}
    DEPENDS ${APPLICATION_ELF}
    COMMENT "Building ${APPLICATION_HEX}"
)

add_custom_command(
    OUTPUT ${APPLICATION_CRC_HEX}
    COMMAND ${SREC_CAT} ${APPLICATION_HEX} -intel
                -exclusive-length-l-e 0x08080004
                -fill 0xFF 0x08080008 0x08080200
                -crc32_little_endian 0x08080000
                -o ${APPLICATION_CRC_HEX} -intel
    DEPENDS ${APPLICATION_HEX}
    COMMENT "Building ${APPLICATION_CRC_HEX}"
)

add_custom_command(
    OUTPUT ${APPLICATION_CRC_BIN}
    COMMAND ${SREC_CAT} ${APPLICATION_CRC_HEX} -intel
                -offset -0x08080000
                -o ${APPLICATION_CRC_BIN} -binary
    DEPENDS ${APPLICATION_CRC_HEX}
    COMMENT "Building ${APPLICATION_CRC_BIN}"
)


# ------------------------------------------------------- BUILD BOOTBLOCK FILES
# Built in bootblock/CMakeLists.txt
# set(BOOTBLOCK_ELF bootblock.elf)

# # Built locally
# set(BOOTBLOCK_HEX bootblock.hex)

# add_custom_command(
#     OUTPUT ${BOOTBLOCK_HEX}
#     COMMAND ${OC} -O ihex $<TARGET_FILE:${BOOTBLOCK_ELF}> ${BOOTBLOCK_HEX}
#     DEPENDS ${BOOTBLOCK_ELF}
#     COMMENT "Building ${BOOTBLOCK_HEX}"
# )


# -------------------------------------------------------- BUILD ASSEMBLY IMAGE
# Built locally
# set(ASSEMBLY_HEX assembly.hex)

# # This pulls in bootblock and application into a single hex file. Note that
# # application is pulled in twice, once for the backup image and once for the
# # run location
# add_custom_command(
#     OUTPUT ${ASSEMBLY_HEX}
#     COMMAND ${SREC_CAT} ${BOOTBLOCK_HEX} -intel
#                 ${APPLICATION_CRC_HEX} -intel -offset -0x000040000
#                 ${APPLICATION_CRC_HEX} -intel
#                 -o ${ASSEMBLY_HEX} -intel
#     DEPENDS ${BOOTBLOCK_HEX} ${APPLICATION_CRC_HEX}
#     COMMENT "Building ${ASSEMBLY_HEX}"
# )


# ------------------------------------------------- SET TARGETS TO BUILD ON ALL
add_custom_target(fwimages ALL
    DEPENDS ${ASSEMBLY_HEX} ${APPLICATION_CRC_BIN}
)


# ------------------------------------------------------------- INSTALL TARGETS
# install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${ASSEMBLY_HEX}
#         RENAME assembly-${SMART_NOZZLE_ASSEMBLY_PN}-${SMART_NOZZLE_BUILD_VERSION}.hex
#         DESTINATION ./
# )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${APPLICATION_CRC_HEX}
        RENAME application_crc-${SMART_NOZZLE_APP_PN}-${SMART_NOZZLE_BUILD_VERSION}.hex
        DESTINATION ./
)

# install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BOOTBLOCK_HEX}
#         RENAME bootblock-${SMART_NOZZLE_BOOT_PN}-${SMART_NOZZLE_BUILD_VERSION}.hex
#         DESTINATION ./
# )
