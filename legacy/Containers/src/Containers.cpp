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

#include "Vector.hpp"
#include "String.hpp"
#include "Map.hpp"

template class CytexLab::Containers::Vector<UINT8>;
template class CytexLab::Containers::Vector<UINT16>;
template class CytexLab::Containers::Vector<UINT32>;
template class CytexLab::Containers::Vector<UINT64>;
template class CytexLab::Containers::Vector<INT8>;
template class CytexLab::Containers::Vector<INT16>;
template class CytexLab::Containers::Vector<INT32>;
template class CytexLab::Containers::Vector<INT64>;
template class CytexLab::Containers::Vector<CytexLab::Containers::String>;
template class CytexLab::Containers::Map<CytexLab::Containers::String, UINT64>;
template class CytexLab::Containers::Map<CytexLab::Containers::String, CytexLab::Containers::String>;