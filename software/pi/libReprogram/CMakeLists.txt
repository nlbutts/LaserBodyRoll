cmake_minimum_required (VERSION 3.5)
project (reprogram)

#add_custom_command(OUTPUT laser.so DEPENDS ${PROJECT_SOURCE_DIR}/liblaser.so COMMAND cp liblaser.so laser.so )
# add_custom_target(laser.so ALL DEPENDS laser.so COMMAND cp liblaser.so laser.so)

add_library(${PROJECT_NAME} STATIC src/cybtldr_api2.c src/cybtldr_api.c src/cybtldr_command.c src/cybtldr_parse.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
#include_directories(${PROJECT_SOURCE_DIR}/include)
