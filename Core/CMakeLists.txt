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

set(MAIN_PACKAGE "CytexLab.Platform.Core")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/%)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Core.Placement)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Core.Placeholders)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Core.Mem)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Core.UTF)