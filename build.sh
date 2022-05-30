#!/bin/bash

BUILD_DIR="stardust_build"

git submodule init
git submodule update

[[ -d "$BUILD_DIR" ]] || mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake ../ && cmake --build . && make
sudo mv stardust /usr/bin
