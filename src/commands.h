#ifndef WASMEDGE_VERIFY_COMMANDS_H
#define WASMEDGE_VERIFY_COMMANDS_H

#include <string_view>

namespace wasmedge_verify {

/**
 * @brief Handles the 'parse' command.
 *
 * @param filename Path to the Wasm file.
 * @return int Exit code.
 */
int runParse(std::string_view filename);

/**
 * @brief Handles the 'validate' command.
 *
 * @param filename Path to the Wasm file.
 * @return int Exit code.
 */
int runValidate(std::string_view filename);

} // namespace wasmedge_verify

#endif // WASMEDGE_VERIFY_COMMANDS_H
