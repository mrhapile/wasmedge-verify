#include "commands.h"
#include <iostream>
#include <string>
#include <wasmedge/wasmedge.h>

namespace wasmedge_verify {

int runParse(std::string_view filename) {
  std::string path(filename);

  WasmEdge_ConfigureContext *ConfCxt = WasmEdge_ConfigureCreate();
  WasmEdge_LoaderContext *Loader = WasmEdge_LoaderCreate(ConfCxt);
  WasmEdge_ASTModuleContext *AST = NULL;
  WasmEdge_Result Res;
  int ExitCode = 0;

  // 3. Parse WASM from file
  Res = WasmEdge_LoaderParseFromFile(Loader, &AST, path.c_str());
  if (!WasmEdge_ResultOK(Res)) {
    std::cerr << "[FAIL] Failed to parse WASM file: " << path << "\n";
    std::cerr << "Error: " << WasmEdge_ResultGetMessage(Res) << "\n";
    ExitCode = 1;
    goto cleanup;
  }

  std::cout << "[OK] WASM parsed successfully\n";

cleanup:
  if (AST) {
    WasmEdge_ASTModuleDelete(AST);
  }
  WasmEdge_LoaderDelete(Loader);
  WasmEdge_ConfigureDelete(ConfCxt);
  return ExitCode;
}

} // namespace wasmedge_verify
