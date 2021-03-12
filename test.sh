#!/bin/bash
rm -rf build
git pull 
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
cd ./build;./qfr_test
