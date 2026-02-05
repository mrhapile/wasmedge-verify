# Design Document - wasmedge-verify

## Purpose
`wasmedge-verify` acts as a specialized, lightweight CLI tool for verifying and investigating WebAssembly binaries. 
While WasmEdge itself provides a runtime CLI, this tool demonstrates how to build custom tooling using the public C API.

## Architecture

The application is structured as a modular console application:

1.  **Main Entry (`main.cpp`)**: 
    - Minimal entry point.
    - Setup and teardown of global resources (if any).
    - Delegates to `runCLI`.

2.  **CLI Dispatcher (`cli.cpp`/`cli.h`)**:
    - Responsible for parsing `argc`/`argv`.
    - Routes commands (`parse`, `validate`) to their respective handlers.
    - Handles top-level error reporting and usage info.

3.  **Command Handlers**:
    - **Parse (`parse.cpp`)**: Uses `WasmEdge_LoaderContext` to load a module into an AST. This confirms the binary format is correct.
    - **Validate (`validate.cpp`)**: Uses `WasmEdge_VMContext` to perform formal validation (type checking, etc.).

## Integration with WasmEdge

- **C API Only**: The tool strictly uses `<wasmedge/wasmedge.h>` and links against `libwasmedge`.
- **No Internal Headers**: It does not depend on internal WasmEdge C++ headers, ensuring ABI stability and compatibility with standard WasmEdge installations.

## CI/CD Friendliness

The tool is designed to be used in CI/CD pipelines:
- **Exit Codes**:
    - `0`: Success (Valid/Parsed).
    - `1`: Failure (Invalid/Error).
- **Streams**:
    - Success messages go to `stdout`.
    - Error messages go to `stderr`.

## Future Extensions
Potential future enhancements (out of scope for current version):
- **Inspect**: Print imports/exports.
- **Convert**: AOT compilation trigger.
- **Statistics**: Count instructions or sections.
