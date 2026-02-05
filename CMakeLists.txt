cmake_minimum_required(VERSION 3.10)

project(wasmedge-verify LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings
if(MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/cli.cpp
)

# Header files (for IDE support)
set(HEADERS
    src/cli.h
)

add_executable(wasmedge-verify ${SOURCES} ${HEADERS})

target_include_directories(wasmedge-verify PRIVATE src)
