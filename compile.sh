#!/bin/bash

# Set source and output directories
SRC_DIR="src"
OUT_DIR="bin"
MAIN_FILE="main.cpp"
OUTPUT="filemanager"

# Create output directory if it doesn't exist
mkdir -p "$OUT_DIR"

# Compile all .cpp files in the source directory
g++ "$SRC_DIR"/*.cpp -o "$OUT_DIR/$OUTPUT" -Wall -Wextra --std=c++20

# Print result
if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable is at $OUT_DIR/$OUTPUT"
else
    echo "Compilation failed."
fi