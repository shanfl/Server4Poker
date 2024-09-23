#!/bin/bash

SCRIPT_PATH=$(readlink -f  "$0")
ROOT_PATH=$(dirname "$SCRIPT_PATH")

echo "======================================================="
echo "SCRIPT_PATH: ${SCRIPT_PATH} ROOT_PATH: ${ROOT_PATH}"
echo "======================================================="

install_wolfssl()
{
    rm -rf ${ROOT_PATH}/3rd/wolfssl/linux
    mkdir -p ${ROOT_PATH}/tmp/wolfssl

    git clone -b v5.7.0-stable --recursive https://github.com/wolfSSL/wolfssl.git   ${ROOT_PATH}/tmp/wolfssl 
    mkdir -p 3rd/wolfssl/linux
    cmake -S ${ROOT_PATH}/tmp/wolfssl  -B ${ROOT_PATH}/tmp/wolfssl/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=./3rd/wolfssl/linux -DBUILD_SHARED_LIBS=OFF
    cmake --build ${ROOT_PATH}/tmp/wolfssl/build --target install --config Release
}

install_protobuf3()
{
    git clone -b v3.26.0 --recursive https://github.com/protocolbuffers/protobuf.git ${ROOT_PATH}/tmp/protobuf 
    mkdir -p 3rd/protobuf3/linux
    cmake -S ${ROOT_PATH}/tmp/protobuf -B ${ROOT_PATH}/tmp/protobuf/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${ROOT_PATH}/3rd/protobuf3/linux -DBUILD_SHARED_LIBS=OFF
    cmake --build ${ROOT_PATH}/tmp/protobuf/build --target install --config Release
}

install_protobuf3
install_wolfssl
