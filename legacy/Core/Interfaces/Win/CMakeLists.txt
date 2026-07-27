#
# CytexLab Platform
# Copyright (c) 2026 CytexLab
#
# Данный файл является частью платформы CytexLab и распространяется
# согласно условиям CytexLab Public Community License (CL2P) v1.0.
# Полный текст лицензии доступен в файле LICENSE.txt.
#
# Для получения коммерческой лицензии: programminyka@mail.ru
#

set(include "include")
set(files 
    "src/WinFabric.cpp"
    "src/SystemImpl.hpp"
    "src/WinImports.hpp"
    "src/ConsoleImpl.hpp"
    "src/ConsoleImpl.cpp"
    "src/FileImpl.hpp"
    "src/FileImpl.cpp"
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
    "src/SystemImpl.Thread.cpp"
    "src/SystemImpl.Pipe.cpp"
    "src/SystemImpl.Allocator.cpp"
    "src/SystemImpl.Args.cpp"
    "src/SystemImpl.Process.cpp"
    "src/SystemImpl.Window.cpp"
    "src/SystemImpl.RenderWindow.cpp"
    "src/ProcessImpl.hpp"
    "src/ProcessImpl.cpp"
    "src/WindowImpl.hpp"
    "src/WindowImpl.cpp"
    "src/RenderWindowImpl.hpp"
    "src/RenderWindowImpl.cpp"
)

set(deps "Base" "Interface")

platform_add_module("WinInterface" "${files}" "${include}" "${deps}")