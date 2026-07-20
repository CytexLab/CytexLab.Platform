/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "String.hpp"
#include "Unicode.hpp"

CytexLab::Containers::String::String(CytexLab::Interface::IAllocator* Allocator) : container(Allocator)
{
    this->container.PushBack(U'\0');
}

CytexLab::Containers::String::~String()
{

}

CytexLab::Containers::String &CytexLab::Containers::String::operator=(LPCECHAR Str)
{
    UINT64 len = Unicode::StrLen(Str);

    this->container.Clear();

    for (UINT64 i = 0; i < len; i++)
        this->container.PushBack(Str[i]);

    this->container.PushBack(U'\0');

    return *this;
}

CytexLab::Containers::String &CytexLab::Containers::String::operator=(const CytexLab::Containers::String &Str)
{
    if (&Str == this)
        return *this;

    UINT64 len = Str.container.GetSize() - 1;

    this->container.Clear();

    for (UINT64 i = 0; i < len; i++)
        this->container.PushBack(Str.container[i]);

    this->container.PushBack(U'\0');

    return *this;
}

CytexLab::Containers::String& CytexLab::Containers::String::operator+=(LPCECHAR Str)
{
    UINT64 len = Unicode::StrLen(Str);

    this->container.PopBack();

    for (UINT64 i = 0; i < len; i++)
        this->container.PushBack(Str[i]);

    this->container.PushBack(U'\0');

    return *this;
}

CytexLab::Containers::String& CytexLab::Containers::String::operator+=(const String& Str)
{
    UINT64 len = Str.container.GetSize() - 1;

    this->container.PopBack();

    for (UINT64 i = 0; i < len; i++)
        this->container.PushBack(Str.container[i]);

    this->container.PushBack(U'\0');

    return *this;
}

BOOL CytexLab::Containers::String::operator==(LPCECHAR Str) const
{
    LPCECHAR ptr = this->container.GetData();

    return Unicode::StrCmp(Str, ptr);
}

BOOL CytexLab::Containers::String::operator==(const CytexLab::Containers::String &Other) const
{
    LPCECHAR ptr1 = this->container.GetData();
    LPCECHAR ptr2 = Other.container.GetData();

    return Unicode::StrCmp(ptr1, ptr2);
}

BOOL CytexLab::Containers::String::operator!=(LPCECHAR Str) const
{
    LPCECHAR ptr = this->container.GetData();

    return !Unicode::StrCmp(Str, ptr);
}

BOOL CytexLab::Containers::String::operator!=(const CytexLab::Containers::String &Other) const
{
    LPCECHAR ptr1 = this->container.GetData();
    LPCECHAR ptr2 = Other.container.GetData();

    return !Unicode::StrCmp(ptr1, ptr2);
}

ECHAR& CytexLab::Containers::String::operator[](UINT64 Index)
{
    return this->container[Index];
}

const ECHAR& CytexLab::Containers::String::operator[](UINT64 Index) const
{
    return this->container[Index];
}

LPCECHAR CytexLab::Containers::String::GetData() const
{
    return this->container.GetData();
}

void CytexLab::Containers::String::Clear()
{
    this->container.Clear();
    this->container.PushBack(U'\0');
}

UINT64 CytexLab::Containers::String::GetSize() const
{
    return this->container.GetSize() - 1;
}

UINT64 CytexLab::Containers::String::GetCapacity() const
{
    return this->container.GetCapacity();
}