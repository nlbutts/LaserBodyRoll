#!/bin/bash

# The script attempts to setup your system to build the Warwick project.


#Main function that handles the one time setup of project files:
main()
{
    python_dev
    setup_cmake

    exit 0
}

#Check if g++ is not installed, if that is the case, download it (needed for srecord)
setup_g++()
{
    echo -e "\n\nsetup_g++()"
    g++ &> /dev/null
    if [ $? == 127 ]; then
        echo "g++ needs to be installed..."
        sudo apt-get install g++
    else
        echo "g++ already installed"
    fi
}

#Check if libboost-dev is not installed, if that is the case, download it (needed for srecord)
setup_libboost-dev()
{
    echo -e "\n\nsetup_libboost-dev()"
    dpkg -s libboost-dev > /dev/null
    if [ $? != 0 ]; then
        echo "libboost-dev needs to be installed..."
        sudo apt-get install libboost-dev
    else
        echo "libboost-dev already installed"
    fi
}

#Check if libtool is not installed, if that is the case, download it (needed for srecord)
setup_libtool()
{
    echo -e "\n\nsetup_libtool()"
    dpkg -s libtool > /dev/null
    if [ $? != 0 ]; then
        echo "libtool needs to be installed..."
        sudo apt-get install libtool
    else
        echo "libtool already installed"
    fi
}

#Check if libgcrypt11-dev is not installed, if that is the case, download it (needed for srecord)
setup_libgcrypt11-dev()
{
    echo -e "\n\nsetup_libgcrypt11-dev()"
    dpkg -s libgcrypt11-dev > /dev/null
    if [ $? != 0 ]; then
        echo "libgcrypt11-dev needs to be installed..."
        sudo apt-get install libgcrypt11-dev
    else
        echo "libgcrypt11-dev already installed"
    fi
}

setup_python_dev()
{
    echo -e "\n\nsetup_python_dev()"
    dpkg -s libgcrypt11-dev > /dev/null
    if [ $? != 0 ]; then
        echo "python-dev needs to be installed..."
        sudo apt-get install python3-dev
    else
        echo "python3-dev already installed"
    fi
}

setup_cmake()
{
    CMAKE_VER=$(cmake --version | grep 'cmake version' | sed s'/cmake version \(.*\)/\1/')
    echo "Cmake Version is: ${CMAKE_VER}"
    if [ ${CMAKE_VER} = "3.8.0" ]
    then
        echo "CMake is up-to-date"
    else
        echo "Building CMake"
        CMAKE_BUILD="cmake_build"
        rm -rf ${CMAKE_BUILD}
        mkdir ${CMAKE_BUILD}
        cd ${CMAKE_BUILD}
        wget https://cmake.org/files/v3.8/cmake-3.8.0.tar.Z
        tar -xf cmake-3.8.0.tar.Z
        cd cmake-3.8.0
        ./configure && make -j4 && sudo make install
    fi

}

#calls main function
main "$@"
