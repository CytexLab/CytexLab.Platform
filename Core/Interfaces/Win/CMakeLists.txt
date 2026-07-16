# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
# 
# CytexLab (c) 2026

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
    "src/PipeImpl.hpp"
    "src/PipeImpl.cpp"
    "src/AllacatorImpl.hpp"
    "src/AllacatorImpl.cpp"
)
set(deps "Base" "Interface")

platform_add_module("WinInterface" "${files}" "${include}" "${deps}")