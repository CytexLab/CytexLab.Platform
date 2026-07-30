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

#include "UTF.hpp"

extern "C" void startup()
{
    LPCCHAR str = "Welcome! Привет мир! 😁";
    ECHAR buf[128];

    cl::UTF::SConvertStringResult result = cl::UTF::ConvertStringUTF8ToUTF32(str, buf);
}