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
    "src/Application.cpp"
    "src/Imports.hpp"
    "src/Mem.asm")
set(include "include")
set(deps "CytexLab.Platform.Core" "CytexLab.Platform.Core.Mem" "CytexLab.Platform.Core.Placement" "CytexLab.Platform.Core.Placeholders" "CytexLab.Platform.Core.UTF.Processor.Symbols")

platform_add_module("${MAIN_PACKAGE}.Windows" "${files}" "${include}" "${deps}")