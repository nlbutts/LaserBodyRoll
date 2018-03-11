#!/bin/bash

# load default path
source /etc/environment

# get current directory
SCRIPT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# get arm compiler directory
COMPILER_DIR=${SCRIPT_DIR}/../toolchain/gcc-arm-none-eabi-5_4-2016q3/bin

JLINK_DIR=/opt/SEGGER/JLink_V610i/

# set new path
export PATH=${COMPILER_DIR}:${JLINK_DIR}:${PATH}
echo Added ${COMPILER_DIR} to PATH
echo Added ${JLINK_DIR} to PATH
