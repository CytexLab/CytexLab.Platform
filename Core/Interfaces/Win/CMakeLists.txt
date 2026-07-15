set(include "include")
set(files 
    "src/WinFabric.cpp"
    "src/SystemImpl.hpp"
    "src/SystemImpl.cpp"
    "src/WinImports.hpp"
    "src/ConsoleImpl.hpp"
    "src/ConsoleImpl.cpp"
    "src/FileImpl.hpp"
    "src/FileImpl.cpp"
    "src/PoolImpl.hpp"
    "src/PoolImpl.cpp"
    "src/ThreadImpl.hpp"
    "src/ThreadImpl.cpp"
    "src/MutexImpl.hpp"
    "src/MutexImpl.cpp"
)
set(deps "Base" "Interface")

platform_add_module("WinInterface" "${files}" "${include}" "${deps}")