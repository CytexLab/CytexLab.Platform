set(include "")
set(files "src/main.cpp")
set(deps "Base" "Interface" "WinInterface")

platform_add_executable("TestRunner" "${files}" "${include}" "${deps}")