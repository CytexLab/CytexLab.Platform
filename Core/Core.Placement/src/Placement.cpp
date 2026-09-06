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

#define CYTEXLAB_CORE_PLACEMENT_API_EXPORT
#include "Placement.hpp"

CYTEXLAB_CORE_PLACEMENT_API LPVOID operator new(UINT64 size, LPVOID mem)
{
  return mem;
}