cmake_minimum_required(VERSION 3.5)
project(CEncode)

set(CMAKE_CXX_STANDARD 17)

add_executable(CEncode main.cpp
        Headers/Binary.h
        Classes/BinaryValue.h
        Sources/Binary.cpp
        Headers/Base64.h
        Sources/Base64.cpp
        Headers/Hex.h
        Sources/Hex.cpp
        Headers/Ascii85.h
        Sources/Ascii85.cpp
        Headers/URL.h
        Sources/URL.cpp
        Headers/Morse.h
        Sources/Morse.cpp
        Headers/Ascii.h
        Sources/Ascii.cpp
)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
endif()