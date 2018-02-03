cmake_minimum_required (VERSION 3.5)
project (reprogram_psoc)


#add_custom_command(OUTPUT laser.so DEPENDS ${PROJECT_SOURCE_DIR}/liblaser.so COMMAND cp liblaser.so laser.so )
# add_custom_target(laser.so ALL DEPENDS laser.so COMMAND cp liblaser.so laser.so)

add_executable(${PROJECT_NAME} src/reprogram_psoc.cpp)
target_link_libraries(${PROJECT_NAME} reprogram tclap)
include_directories(${PROJECT_SOURCE_DIR}/include)
