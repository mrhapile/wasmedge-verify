#include "commands.h"
#include <iostream>
#include <wasmedge/wasmedge.h>

namespace wasmedge_verify {

int runParse(std::string_view filename) {
  // Phase 2: Placeholder that ensures WasmEdge headers are available.
  // No real parsing logic yet.
  std::cout << "parse command invoked for " << filename << "\n";
  std::cout << "WasmEdge C API header included successfully.\n";
  return 0;
}

} // namespace wasmedge_verify
