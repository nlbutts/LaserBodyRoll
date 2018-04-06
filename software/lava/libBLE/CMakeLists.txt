# ------------------------------------------------------- MINIMUM CMAKE VERSION
cmake_minimum_required(VERSION 3.4)

# ---------------------------------------------------------------- PROJECT NAME
set(LOCAL_PROJ_NAME ble)

# -------------------------------------------------------------- FIND SRC FILES
set(SRC_FILES src/ble_protocol.c)

# --------------------------------------------- FILE EXCLUSION FOR X86/UT BUILD

# --------------------------------------------------------- DEFINE BUILD TARGET
add_library(${LOCAL_PROJ_NAME} STATIC ${SRC_FILES})

# -------------------------------------------------------------- FIND SRC FILES
target_include_directories(${LOCAL_PROJ_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
