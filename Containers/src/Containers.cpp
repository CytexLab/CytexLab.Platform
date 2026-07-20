/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
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