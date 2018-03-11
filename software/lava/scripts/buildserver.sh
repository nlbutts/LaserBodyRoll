#!/bin/bash

# ------------------------------------------------------------- Local functions

# $1 File to check, error returned if it does not exist
function assert_file_exists()
{
    if [[ ! -e $1 ]]; then
        printf "\n[ERROR - ${LINENO}] Artifact ${1} does not exist\n"
        exit 1
    else
        printf "Found artifact ${1}\n"
    fi
}


# ---------------------------------------------------------- Build sanity check
if [ -z "$SMART_NOZZLE_BUILD_VERSION" ]; then
    printf "\n[ERROR - ${LINENO}] Please define SMART_NOZZLE_BUILD_VERSION\n"
    printf "\t e.g. export SMART_NOZZLE_BUILD_VERSION=\"1.0.1.999999\"\n\n"
    exit 1
fi


if [ -z "$SMART_NOZZLE_APP_PN" ]; then
    printf "\n[ERROR - ${LINENO}] Please define SMART_NOZZLE_APP_PN\n"
    printf "\t e.g. export SMART_NOZZLE_APP_PN=\"501010-000XXXxXX\"\n\n"
    exit 1
fi


if [ -z "$SMART_NOZZLE_BOOT_PN" ]; then
    printf "\n[ERROR - ${LINENO}] Please define SMART_NOZZLE_BOOT_PN\n"
    printf "\t e.g. export SMART_NOZZLE_BOOT_PN=\"501010-000XXXxXX\"\n\n"
    exit 1
fi


if [ -z "${SMART_NOZZLE_ASSEMBLY_PN}" ]; then
    printf "\n[ERROR - ${LINENO}] Please define SMART_NOZZLE_ASSEMBLY_PN\n"
    printf "\t e.g. export SMART_NOZZLE_ASSEMBLY_PN=\"501010-000XXXxXX\"\n\n"
    exit 1
fi

if [ -z "${HW_COMP}" ]; then
    printf "\n[ERROR - ${LINENO}] Please define HW_COMP\n"
    printf "\t e.g. export HW_COMP=1"
    exit 1
fi

# --------------------------------- Get the directory that this script lives in
SCRIPT_WORKING_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
PROJECT_DIR=${SCRIPT_WORKING_DIR}/..


# ----------------------------------------------------------------------- Build
(
    printf "Entering build directory...\n"
    pushd ${PROJECT_DIR} || exit 1

    ./generate_build.sh || exit 1

    make -C build/arm       install -j4 || exit 1
    make -C build/x86       install -j4 || exit 1

    printf "Leaving build directory...\n"
    popd
)

if ! [ "$?" = "0" ]; then
    printf "\n[ERROR - ${LINENO}] Build step failed\n"
    exit 1
fi


# --------------------------------------------------- Generate the update image
(
    arm_build_output=${PROJECT_DIR}/build/arm/build_output
    update_image=${arm_build_output}/application-${SMART_NOZZLE_APP_PN}-${SMART_NOZZLE_BUILD_VERSION}.image

    ${SCRIPT_WORKING_DIR}/create_update_image.sh ${update_image} ${HW_COMP} || exit 1

    assert_file_exists ${update_image} || exit 1
)

if ! [ "$?" = "0" ]; then
    printf "\n[ERROR - ${LINENO}] Build step failed\n"
    exit 1
fi


# --------------------------------------- Check that the output artifacts exist
(
    printf "Checking for build artifacts...\n"
    artifact_dir=${PROJECT_DIR}/build/arm/build_output

    # Check that the bootblock files exist
    assert_file_exists \
        ${artifact_dir}/bootblock-${SMART_NOZZLE_BOOT_PN}-${SMART_NOZZLE_BUILD_VERSION}.elf \
        || exit 1
    assert_file_exists \
        ${artifact_dir}/bootblock-${SMART_NOZZLE_BOOT_PN}-${SMART_NOZZLE_BUILD_VERSION}.hex \
        || exit 1

    # Check that the application files exist
    assert_file_exists \
        ${artifact_dir}/application-${SMART_NOZZLE_APP_PN}-${SMART_NOZZLE_BUILD_VERSION}.elf \
        || exit 1
    assert_file_exists \
        ${artifact_dir}/application_crc-${SMART_NOZZLE_APP_PN}-${SMART_NOZZLE_BUILD_VERSION}.hex \
        || exit 1

    # Check that the assembly files exist
    assert_file_exists \
        ${artifact_dir}/assembly-${SMART_NOZZLE_ASSEMBLY_PN}-${SMART_NOZZLE_BUILD_VERSION}.hex \
        || exit 1

    # Check that the unit tests built
    assert_file_exists ${PROJECT_DIR}/build/x86/build_output/ut || exit 1
)

if ! [ "$?" = "0" ]; then
    printf "\n[ERROR - ${LINENO}] Build artifacts are missing\n"
    exit 1
fi


# -------------------------------------------------------------- Run unit tests
(
    printf "Entering test directory...\n"
    pushd ${PROJECT_DIR}/build/x86/build_output

    # Run the unit tests
    ./ut --gtest_output=xml:test_detail.xml

    # Generate the coverage report
    printf "Generating the coverage report...\n"
    ${PROJECT_DIR}/scripts/gcovr -r ${PROJECT_DIR} \
         -e "(ut/googletest*)|(ut/src/*)|(ut/include/*)|(third-party/*)|(imagegen/*)" \
        --xml > unit_test_coverage.xml

    printf "Leaving test directory...\n"
    popd
)

if ! [ "$?" = "0" ]; then
    printf "\n[WARNING - ${LINENO}] Unit tests did not pass\n"
fi
