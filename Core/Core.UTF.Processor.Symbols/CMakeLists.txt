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

add_library("${MAIN_PACKAGE}.UTF.Processor.Symbols" SHARED)
target_sources("${MAIN_PACKAGE}.UTF.Processor.Symbols" PRIVATE
  src/UTF.Processor.cpp
)
target_include_directories("${MAIN_PACKAGE}.UTF.Processor.Symbols" PUBLIC include)
target_link_libraries("${MAIN_PACKAGE}.UTF.Processor.Symbols" PUBLIC
  CompileFlagsLibrary
  CompileDefine
  LinkFlagsLibrary
  "${MAIN_PACKAGE}.Mem"
  "${MAIN_PACKAGE}.API"
)
set_target_properties("${MAIN_PACKAGE}.UTF.Processor.Symbols" PROPERTIES PREFIX "")
