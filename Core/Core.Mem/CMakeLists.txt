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

set(files "src/Mem.cpp")
set(include "include")
set(deps "${MAIN_PACKAGE}")

platform_add_module("${MAIN_PACKAGE}.Mem" "${files}" "${include}" "${deps}")