# wasmedge-verify

A minimal, production-quality CLI tool for verifying WebAssembly modules using the WasmEdge C API.
Currently in Phase 1 (Prototype/Skeleton).

## Overview

`wasmedge-verify` is designed to parse and validate `.wasm` binaries. It serves as a lightweight utility to check WebAssembly modules before execution.

## Build Instructions

Requirements:
- CMake 3.10+
- C++17 compliant compiler
- Linux or macOS

```bash
mkdir build && cd build
cmake ..
make
```

## Usage

### Parse a WASM file
```bash
./wasmedge-verify parse my_module.wasm
```

### Validate a WASM file
```bash
./wasmedge-verify validate my_module.wasm
```

## Phase 1 Status
- [x] Project Skeleton
- [x] CLI Argument Parsing
- [ ] WasmEdge Integration (Planned for Phase 2)
