#include "commands.h"
#include <iostream>
#include <string>
#include <wasmedge/wasmedge.h>

namespace wasmedge_verify {

int runValidate(std::string_view filename) {
  // Convert string_view to std::string to ensure null-termination for C API
  std::string fileStr(filename);

  // 1. Create Configure Context
  WasmEdge_ConfigureContext *ConfCxt = WasmEdge_ConfigureCreate();

  // 2. Create VM Context
  // We do not register WASI or other host modules as per strict scope
  // requirements.
  WasmEdge_VMContext *VMCxt = WasmEdge_VMCreate(ConfCxt, NULL);

  // 3. Load WASM from file
  WasmEdge_Result Res = WasmEdge_VMLoadWasmFromFile(VMCxt, fileStr.c_str());
  if (!WasmEdge_ResultOK(Res)) {
    std::cerr << "[FAIL] Failed to load WASM file: " << fileStr << "\n";
    std::cerr << "Error: " << WasmEdge_ResultGetMessage(Res) << "\n";

    WasmEdge_VMDelete(VMCxt);
    WasmEdge_ConfigureDelete(ConfCxt);
    return 1;
  }

  // 4. Validate WASM
  Res = WasmEdge_VMValidate(VMCxt);
  if (!WasmEdge_ResultOK(Res)) {
    std::cerr << "[FAIL] WASM validation failed\n";
    std::cerr << "Error: " << WasmEdge_ResultGetMessage(Res) << "\n";

    WasmEdge_VMDelete(VMCxt);
    WasmEdge_ConfigureDelete(ConfCxt);
    return 1;
  }

  // 5. Success
  std::cout << "[OK] WASM validation passed\n";

  // Cleanup
  WasmEdge_VMDelete(VMCxt);
  WasmEdge_ConfigureDelete(ConfCxt);

  return 0;
}

} // namespace wasmedge_verify
