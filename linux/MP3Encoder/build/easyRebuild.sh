#!/bin/bash

cd release
make clean
rm -rf __ CMakeCache.txt CMakeFiles cmake_install.cmake Makefile

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DPROJECT_NAME:STRING=MP3Encoder
make -j4

