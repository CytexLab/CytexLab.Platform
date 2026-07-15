set(include "include")
set(files 
    "src/Interface.cpp"
)
set(deps "Base")

platform_add_module("Interface" "${files}" "${include}" "${deps}")