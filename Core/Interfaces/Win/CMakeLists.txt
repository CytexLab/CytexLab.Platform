# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
# 
# CytexLab (c) 2026

set(include "include")
set(files 
    "src/WinFabric.cpp"
    "src/SystemImpl.hpp"
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
    "src/AllocatorImpl.hpp"
    "src/AllocatorImpl.cpp"
    "src/SystemImpl.Base.cpp"
    "src/SystemImpl.Console.cpp"
    "src/SystemImpl.File.cpp"
    "src/SystemImpl.Pool.cpp"
    "src/SystemImpl.Thread.cpp"
    "src/SystemImpl.Pipe.cpp"
    "src/SystemImpl.Allocator.cpp"
    "src/SystemImpl.Args.cpp"
    "src/SystemImpl.Process.cpp"
    "src/ProcessImpl.hpp"
    "src/ProcessImpl.cpp"
)

set(deps "Base" "Interface")

platform_add_module("WinInterface" "${files}" "${include}" "${deps}")