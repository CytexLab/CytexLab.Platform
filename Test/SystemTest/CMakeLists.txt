set(files "src/main.cpp")
set(deps "Base" "Interface" "WinInterface")

platform_add_executable("SystemTest" "${files}" "" "${deps}")