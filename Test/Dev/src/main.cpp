/*
 * CytexLab Platform
 * Copyright (c) 2026 CytexLab
 *
 * Данный файл является частью платформы CytexLab и распространяется
 * согласно условиям CytexLab Public Community License (CL2P) v1.0.
 * Полный текст лицензии доступен в файле LICENSE.txt.
 *
 * Для получения коммерческой лицензии: programminyka@mail.ru
 */

#include "Mem.hpp"
#include "UTF.hpp"

extern "C" void startup()
{
    INT64 num = -1000;
    LPCECHAR str = U"25";

    cl::UTF::SStringFunctionsResult result = cl::UTF::StringToSInt(str, &num);
}