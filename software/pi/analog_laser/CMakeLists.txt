cmake_minimum_required (VERSION 3.5)
project (analog_laser)


add_executable(${PROJECT_NAME} src/analog_logic.cpp src/main.cpp)
target_link_libraries(${PROJECT_NAME} laser tclap wiringPi)
include_directories(${PROJECT_SOURCE_DIR}/include)
