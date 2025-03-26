# VideoSDK

A C++ SDK for real-time video encoding and decoding.

## Dependencies
Dependencies are included in the `3rdparty` directory:
- libswscale
- libavcodec
- x264

## Preview
![Preview](https://raw.githubusercontent.com/libmini/DWebUI/refs/heads/main/Preview.png)

## Build Instructions
1. Ensure `3rdparty` contains the required libraries and headers.
2. Create build directory: `mkdir build && cd build`
3. Run CMake: `cmake ..`
4. Build: `make`
5. Run example: `./bin/example`

## Usage
See `example/main.cpp` for a usage example.