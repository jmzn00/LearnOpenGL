#!/bin/bash
set -e

cmake --build build -j$(nproc)
./build/LearnOpenGL
