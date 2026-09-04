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
    "src/main.cpp"
    "src/mem.asm")
set(deps "CytexLab.Platform.Core.Placement" "CytexLab.Platform.Core.Placeholders" "CytexLab.Platform.Core.Mem")
set(include "")

platform_add_executable("Dev" "${files}" "${include}" "${deps}")