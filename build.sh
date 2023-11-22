#!/usr/bin/env bash
set -ex

VERSION=$1
BUILD_NUMBER=$2

mkdir -p build
pushd build &> /dev/null
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DPROJECT_VERSION=$VERSION -DBUILD_NUMBER=$BUILD_NUMBER ..
cmake --build .
cpack
popd &> /dev/null

