#!/bin/bash
set -euo pipefail

APP_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )"/.. >/dev/null 2>&1 && pwd )"

if [[ $(uname -s) == CYGWIN* ]];then
APP_ROOT=$(cygpath -w "$APP_ROOT")
fi

set -x 

BUILD_CONTEXT="${BUILD_CONTEXT:-dev}"
BUILD_DIR="$APP_ROOT/build-${BUILD_CONTEXT}"

mkdir -p "$BUILD_DIR"

CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD:-98}
CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE:-Release}
BUILD_TESTS=${BUILD_TESTS:-OFF}

cmake -GNinja \
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
        -DCMAKE_CXX_STANDARD=$CMAKE_CXX_STANDARD \
        -DINSTALL_FOLDER=$BUILD_DIR/install \
        -DBUILD_TESTS=$BUILD_TESTS \
        ${@:1} \
        -Wno-dev \
        -S "$APP_ROOT" \
        -B "$BUILD_DIR"

nice cmake --build "$BUILD_DIR" --target all
cmake --install "$BUILD_DIR"
