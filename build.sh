#!/bin/bash
set -e  # Exit immediately if a command exits with a non-zero status.

# 1. Create build directory
mkdir -p build

# 2. Configure
echo "Configuring..."
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

# 3. Build
echo "Building..."
cmake --build build --parallel 4  # --j4 uses 4 CPU cores for speed

# 4. Run Tests
echo "Running Tests..."
cd build
ctest -C Debug --output-on-failure
cd ..