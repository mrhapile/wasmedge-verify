# FindWasmEdge.cmake
# Finds the WasmEdge library and headers.

find_path(WASMEDGE_INCLUDE_DIR 
    NAMES wasmedge/wasmedge.h
    PATHS 
        /opt/homebrew/include
        /usr/local/include
        /usr/include
        $ENV{HOME}/.wasmedge/include
)

find_library(WASMEDGE_LIB 
    NAMES wasmedge
    PATHS 
        /opt/homebrew/lib
        /usr/local/lib
        /usr/lib
        $ENV{HOME}/.wasmedge/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WasmEdge 
    REQUIRED_VARS WASMEDGE_LIB WASMEDGE_INCLUDE_DIR
)

if(WasmEdge_FOUND AND NOT TARGET WasmEdge::wasmedge_c)
    add_library(WasmEdge::wasmedge_c UNKNOWN IMPORTED)
    set_target_properties(WasmEdge::wasmedge_c PROPERTIES
        IMPORTED_LOCATION "${WASMEDGE_LIB}"
        INTERFACE_INCLUDE_DIRECTORIES "${WASMEDGE_INCLUDE_DIR}"
    )
endif()
