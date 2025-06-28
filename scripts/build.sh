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
CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE:-Debug}

SCRUTINYTEST_BUILD_TESTS=${SCRUTINYTEST_BUILD_TESTS:-OFF}
SCRUTINYTEST_DISABLE_EXCEPTIONS=${SCRUTINYTEST_DISABLE_EXCEPTIONS:-OFF}
SCRUTINYTEST_NO_DETAILS=${SCRUTINYTEST_NO_DETAILS:-OFF}
SCRUTINYTEST_NO_OUTPUT=${SCRUTINYTEST_NO_OUTPUT:-OFF}
SCRUTINYTEST_MAX_TEST_CASES=${SCRUTINYTEST_MAX_TEST_CASES:-1024}

cmake   -GNinja                                                                 \
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}                                  \
        -DCMAKE_CXX_STANDARD=$CMAKE_CXX_STANDARD                                \
        -DINSTALL_FOLDER=$BUILD_DIR/install                                     \
        -DSCRUTINYTEST_BUILD_TESTS=$SCRUTINYTEST_BUILD_TESTS                    \
        -DSCRUTINYTEST_DISABLE_EXCEPTIONS=$SCRUTINYTEST_DISABLE_EXCEPTIONS      \
        -DSCRUTINYTEST_NO_DETAILS=$SCRUTINYTEST_NO_DETAILS                      \
        -DSCRUTINYTEST_NO_OUTPUT=$SCRUTINYTEST_NO_OUTPUT                        \
        -DSCRUTINYTEST_MAX_TEST_CASES=$SCRUTINYTEST_MAX_TEST_CASES              \
        ${@:1}                                                                  \
        -Wno-dev                                                                \
        -S "$APP_ROOT"                                                          \
        -B "$BUILD_DIR"

nice cmake --build "$BUILD_DIR" --target all
cmake --install "$BUILD_DIR"
