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

add_library("${MAIN_PACKAGE}" SHARED)
target_sources("${MAIN_PACKAGE}" PRIVATE
  "src/Core.cpp"
)
target_link_libraries("${MAIN_PACKAGE}" PRIVATE 
  "CompileFlagsLibrary"
  "CompileDefine"
  "LinkFlagsLibrary"
  "${MAIN_PACKAGE}.API"
)
set_target_properties("${MAIN_PACKAGE}" PROPERTIES PREFIX "")
