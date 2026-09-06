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

#pragma once

#include "Platform.hpp"

#ifdef CYTEXLAB_CORE_PLACEMENT_API_EXPORT
#define CYTEXLAB_CORE_PLACEMENT_API __declspec(dllexport)
#else
#define CYTEXLAB_CORE_PLACEMENT_API __declspec(dllimport)
#endif

CYTEXLAB_CORE_PLACEMENT_API LPVOID operator new(UINT64 size, LPVOID mem);