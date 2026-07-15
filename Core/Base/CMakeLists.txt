set(include "include")
set(files 
    "src/Base.cpp"
    "src/Mem.cpp"
    "src/Placement.cpp"
    "src/Unicode.cpp"
)
set(deps "")

platform_add_module("Base" "${files}" "${include}" "${deps}")