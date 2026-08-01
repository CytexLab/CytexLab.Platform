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

set(files
    "src/Win32.SystemImpl.hpp"
    "src/Win32.SystemImpl.cpp"
    "src/Win32.Fabric.cpp"
    "src/Win32.WinImports.hpp")
set(include "include")
set(deps "CytexLab.Platform.Core")

platform_add_module("CytexLab.Platform.SystemPlatform" "${files}" "${include}" "${deps}")