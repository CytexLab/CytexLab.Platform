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

set (SUB_UTF_PACKAGE "${MAIN_UTF_PACKAGE}.Processor")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/%.Processor.Symbols)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/%.Processor.String)