cmake_minimum_required(VERSION 3.10)

project(wasmedge-verify LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add cmake module path for FindWasmEdge.cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Compiler warnings
if(MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find WasmEdge
find_package(WasmEdge REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/cli.cpp
    src/parse.cpp
    src/validate.cpp
)

# Header files (for IDE support)
set(HEADERS
    src/cli.h
    src/commands.h
)

add_executable(wasmedge-verify ${SOURCES} ${HEADERS})

target_include_directories(wasmedge-verify PRIVATE src)

# Link WasmEdge C API
target_link_libraries(wasmedge-verify PRIVATE WasmEdge::wasmedge_c)
