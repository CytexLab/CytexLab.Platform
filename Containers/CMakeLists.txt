set(files
    "src/String.cpp"
)
set(deps "Base" "Interface")
set(include "include")

platform_add_module("Containers" "${files}" "${include}" "${deps}")