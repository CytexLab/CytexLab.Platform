/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#pragma once

#include "IAllocator.hpp"
#include "Mem.hpp"

namespace CytexLab
{
    namespace Containers
    {
        template <typename T>
        class Vector
        {
        private:
            CytexLab::Interface::IAllocatorHandle mem;
            CytexLab::Interface::IAllocator* allocator;

            UINT64 size;
            UINT64 capacity;

        public:
            static const UINT64 DefaultCapacity = 2;

            Vector(CytexLab::Interface::IAllocator* Allocator)
            {
                this->allocator = Allocator;

                this->allocator->Allocate(this->mem, sizeof(T) * DefaultCapacity);

                this->size = 0;
                this->capacity = DefaultCapacity;
            }

            ~Vector()
            {
                this->allocator->Free(this->mem);
            }

            Vector(const Vector&) = delete;
            Vector& operator=(const Vector&) = delete;

            void PushBack(T Obj)
            {
                if (this->size == this->capacity)
                {
                    CytexLab::Interface::IAllocatorHandle new_mem;
                    this->allocator->Allocate(new_mem, sizeof(T) * this->capacity * 2);

                    LPVOID old_mem = this->allocator->Resolve(this->mem);
                    LPVOID new_mem_ptr = this->allocator->Resolve(new_mem);

                    memcpy(new_mem_ptr, old_mem, sizeof(T) * this->capacity);

                    this->allocator->Free(this->mem);
                    this->mem = new_mem;
                    this->capacity *= 2;
                }

                T* mem = (T*) this->allocator->Resolve(this->mem);

                mem[this->size] = Obj;
                this->size++;
            }

            void PopBack()
            {
                if (this->size == 0) return;

                this->size--;
            }

            void Clear()
            {
                this->size = 0;
            }

            void Reserve(UINT64 Size)
            {
                if (this->capacity < this->size + Size)
                {
                    UINT64 newCapacity = this->capacity + Size;

                    CytexLab::Interface::IAllocatorHandle new_mem;

                    LPVOID old_mem = this->allocator->Resolve(this->mem);
                    LPVOID new_mem_ptr = this->allocator->Resolve(new_mem);

                    memcpy(new_mem_ptr, old_mem, sizeof(T) * this->size);

                    this->allocator->Free(this->mem);
                    this->mem = new_mem;
                    this->capacity = newCapacity;
                }
            }

            T& operator[] (UINT64 Index)
            {
                T* mem = (T*) this->allocator->Resolve(this->mem);
                return mem[Index];
            }

            const T& operator[] (UINT64 Index) const
            {
                T* mem = (T*) this->allocator->Resolve(this->mem);
                return mem[Index];
            }

            UINT64 GetSize() const
            {
                return this->size;
            }

            UINT64 GetCapacity() const
            {
                return this->capacity;
            }
        };
    }
}