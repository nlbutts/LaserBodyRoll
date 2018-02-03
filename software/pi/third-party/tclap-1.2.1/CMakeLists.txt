# ------------------------------------------------------- MINIMUM CMAKE VERSION
cmake_minimum_required(VERSION 3.4)


# ---------------------------------------------------------------- PROJECT NAME
set(THIS tclap)

# --------------------------------------------------------------- EXTRACT TCLAP
if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/tclap-1.2.1/README")
   message(STATUS "TCLAP needs to be extracted")
   execute_process(COMMAND tar -xf ${CMAKE_CURRENT_LIST_DIR}/../tclap-1.2.1.tar.gz -C ${CMAKE_CURRENT_LIST_DIR}/..)
else()
   message(STATUS "TCLAP good")
endif()

# --------------------------------------------------------------- DEFINE TARGET
add_library(${THIS} INTERFACE)


# -------------------------------------------------------------- FIND SRC FILES
file(GLOB_RECURSE TCLAP_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/*.h)
target_sources(${THIS} INTERFACE ${TCLAP_HEADERS})


# --------------------------------------------------------------------- INCLUDE
target_include_directories(${THIS} INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
