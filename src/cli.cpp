#include "cli.h"
#include "commands.h"
#include <iostream>
#include <string>
#include <string_view>

namespace wasmedge_verify {

void printUsage(const char *progName) {
  std::cerr << "Usage: " << progName << " <command> [options] <file.wasm>\n"
            << "\nCommands:\n"
            << "  parse <file.wasm>     Parse the WebAssembly file\n"
            << "  validate <file.wasm>  Validate the WebAssembly file\n";
}

int runCLI(int argc, char *argv[]) {
  if (argc < 2) {
    printUsage(argv[0]);
    return 1;
  }

  std::string_view command = argv[1];

  if (command == "parse") {
    if (argc < 3) {
      std::cerr
          << "Error: valid path to a WASM file is required for 'parse'.\n";
      return 1;
    }
    std::string_view filename = argv[2];
    return runParse(filename);
  } else if (command == "validate") {
    if (argc < 3) {
      std::cerr
          << "Error: valid path to a WASM file is required for 'validate'.\n";
      return 1;
    }
    std::string_view filename = argv[2];
    return runValidate(filename);
  } else {
    std::cerr << "Error: Unknown command '" << command << "'.\n";
    printUsage(argv[0]);
    return 1;
  }
}

} // namespace wasmedge_verify
