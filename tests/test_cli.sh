#!/bin/bash
set -e

# Configuration
BIN="./build/wasmedge-verify"
VALID_WASM="tests/valid.wasm"
INVALID_WASM="tests/invalid.wasm"

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo "========================================"
echo "Running wasmedge-verify CLI Test Suite"
echo "========================================"

# 1. Setup
echo "[SETUP] Creating test files..."
# Create a minimal valid WASM module (magic + version)
printf "\x00\x61\x73\x6d\x01\x00\x00\x00" > "$VALID_WASM"
# Create an invalid file
echo "this is not wasm" > "$INVALID_WASM"

cleanup() {
    rm -f "$VALID_WASM" "$INVALID_WASM"
}
trap cleanup EXIT

# 2. Test Function
run_test() {
    local cmd="$1"
    local file="$2"
    local expected_exit="$3"
    local desc="$4"

    echo -n "Testing '$cmd $file' ($desc)... "
    
    set +e
    $BIN $cmd "$file" > /dev/null 2>&1
    local exit_code=$?
    set -e

    if [ $exit_code -eq $expected_exit ]; then
        echo -e "${GREEN}PASS${NC}"
    else
        echo -e "${RED}FAIL${NC} (Expected $expected_exit, got $exit_code)"
        exit 1
    fi
}

# 3. Execution
# Check binary exists
if [ ! -f "$BIN" ]; then
    echo -e "${RED}Error: Binary $BIN not found. Build project first.${NC}"
    exit 1
fi

# Parsing Tests
run_test "parse" "$VALID_WASM" 0 "Valid WASM"
run_test "parse" "$INVALID_WASM" 1 "Invalid WASM"

# Validation Tests
run_test "validate" "$VALID_WASM" 0 "Valid WASM"
run_test "validate" "$INVALID_WASM" 1 "Invalid WASM"

echo "========================================"
echo -e "${GREEN}All tests passed successfully!${NC}"
echo "========================================"
