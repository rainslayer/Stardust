#!/bin/bash

BUILD_DIR="stardust_build"

if [ "$1" == "-c" ];
then
  rm -rf "$BUILD_DIR"
  mkdir "$BUILD_DIR"
fi

clear
[[ -d "$BUILD_DIR" ]] || mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake ../ && cmake --build . && make
