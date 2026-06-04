#!/usr/bin/env bash

set -e

echo "Installing OpenGL dependencies..."

sudo apt update

sudo apt install -y \
    build-essential \
    cmake \
    libglfw3-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev
