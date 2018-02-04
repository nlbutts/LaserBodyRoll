cmake_minimum_required (VERSION 3.5)
project (reprogram)

add_library(${PROJECT_NAME} STATIC src/cybtldr_api2.c src/cybtldr_api.c src/cybtldr_command.c src/cybtldr_parse.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
