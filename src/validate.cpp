#include "commands.h"
#include <iostream>
#include <string>
#include <wasmedge/wasmedge.h>

namespace wasmedge_verify {

int runValidate(std::string_view filename) {
  std::string path(filename);

  WasmEdge_ConfigureContext *ConfCxt = WasmEdge_ConfigureCreate();
  WasmEdge_VMContext *VMCxt = WasmEdge_VMCreate(ConfCxt, NULL);
  WasmEdge_Result Res;
  int ExitCode = 0;

  // 3. Load WASM from file
  Res = WasmEdge_VMLoadWasmFromFile(VMCxt, path.c_str());
  if (!WasmEdge_ResultOK(Res)) {
    std::cerr << "[FAIL] Failed to load WASM file: " << path << "\n";
    std::cerr << "Error: " << WasmEdge_ResultGetMessage(Res) << "\n";
    ExitCode = 1;
    goto cleanup;
  }

  // 4. Validate WASM
  Res = WasmEdge_VMValidate(VMCxt);
  if (!WasmEdge_ResultOK(Res)) {
    std::cerr << "[FAIL] WASM validation failed\n";
    std::cerr << "Error: " << WasmEdge_ResultGetMessage(Res) << "\n";
    ExitCode = 1;
    goto cleanup;
  }

  std::cout << "[OK] WASM validation passed\n";

cleanup:
  WasmEdge_VMDelete(VMCxt);
  WasmEdge_ConfigureDelete(ConfCxt);
  return ExitCode;
}

} // namespace wasmedge_verify
