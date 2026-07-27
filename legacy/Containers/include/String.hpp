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