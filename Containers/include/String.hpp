/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#pragma once

#include "Vector.hpp"

namespace CytexLab
{
    namespace Containers
    {
        class String
        {
        private:
            Vector<ECHAR> container;

        public:
            String(CytexLab::Interface::IAllocator* Allocator);
            ~String();

            String& operator=(LPCECHAR Str);
            String& operator=(const String& Str);

            String& operator+=(LPCECHAR Str);
            String& operator+=(const String& Str);

            BOOL operator==(const String& Other) const;
            BOOL operator==(LPCECHAR Str) const;

            BOOL operator!=(const String& Other) const;
            BOOL operator!=(LPCECHAR Str) const;

            void Clear();

            ECHAR& operator[](UINT64 Index);
            const ECHAR& operator[] (UINT64 Index) const;

            LPCECHAR GetData() const;

            UINT64 GetSize() const;
            UINT64 GetCapacity() const;
        };
    }
}