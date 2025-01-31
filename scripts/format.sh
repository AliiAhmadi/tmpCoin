#!/bin/bash

SRC_DIR="./src"

STYLE="file"

find "$SRC_DIR" -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -i --style=$STYLE {} +

echo "C++ files in '$SRC_DIR' formatted successfully."