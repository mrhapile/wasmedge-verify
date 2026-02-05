# wasmedge-verify

A lightweight, production-quality CLI tool for verifying WebAssembly modules using the [WasmEdge C API](https://wasmedge.org/docs/embed/c/intro).

This tool serves as a minimal example of how to build standalone ecosystem tools that interface with WasmEdge without linking the full runtime for execution.

## Features

- **Parse**: Verifies that a `.wasm` file can be successfully loaded and parsed into an AST.
- **Validate**: Performs WebAssembly validation checks (types, structure) on the module.
- **Minimal Dependencies**: Links only against the WasmEdge C API shared library.

## Build Instructions

### Prerequisites
- CMake 3.10+
- C++17 compliant compiler (GCC/Clang)
- WasmEdge installed system-wide (e.g., via Homebrew or apt)

### Building
```bash
mkdir build && cd build
cmake ..
make
```

## Usage

### 1. Parse a Module
Checks if the file is a syntactically correct WebAssembly binary.
```bash
./wasmedge-verify parse my_module.wasm
```
**Output:**
- `[OK] WASM parsed successfully` (Exit 0)
- `[FAIL] Failed to parse WASM file...` (Exit 1)

### 2. Validate a Module
Performs validation logic to ensure the module is safe to execute.
```bash
./wasmedge-verify validate my_module.wasm
```
**Output:**
- `[OK] WASM validation passed` (Exit 0)
- `[FAIL] WASM validation failed` (Exit 1)

## Development

Run the test suite to verify functionality:
```bash
./tests/test_cli.sh
```

## License
MIT
