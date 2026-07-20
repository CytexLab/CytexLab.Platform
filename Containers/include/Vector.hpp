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
#include "Placement.hpp"

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

            void DestroyElements()
            {
                T* data = (T*)this->allocator->Resolve(this->mem);
                for (UINT64 i = 0; i < this->size; i++)
                {
                    data[i].~T();
                }
            }

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
                this->DestroyElements();
                this->allocator->Free(this->mem);
            }

            Vector(const Vector& other)
            {
                this->allocator = other.allocator;
                this->size = other.size;
                this->capacity = other.capacity;

                this->allocator->Allocate(this->mem, sizeof(T) * this->capacity);

                T* src = (T*)this->allocator->Resolve(other.mem);
                T* dst = (T*)this->allocator->Resolve(this->mem);

                for (UINT64 i = 0; i < this->size; i++)
                {
                    new (&dst[i]) T(src[i]);
                }
            }

            Vector& operator=(const Vector& other)
            {
                if (this == &other)
                    return *this;

                this->DestroyElements();
                this->allocator->Free(this->mem);

                this->allocator = other.allocator;
                this->size = other.size;
                this->capacity = other.capacity;

                this->allocator->Allocate(this->mem, sizeof(T) * this->capacity);

                T* src = (T*)this->allocator->Resolve(other.mem);
                T* dst = (T*)this->allocator->Resolve(this->mem);

                for (UINT64 i = 0; i < this->size; i++)
                {
                    new (&dst[i]) T(src[i]);
                }

                return *this;
            }

            void PushBack(const T& obj)
            {
                if (this->size == this->capacity)
                {
                    CytexLab::Interface::IAllocatorHandle new_mem;
                    this->allocator->Allocate(new_mem, sizeof(T) * this->capacity * 2);

                    T* old_data = (T*)this->allocator->Resolve(this->mem);
                    T* new_data = (T*)this->allocator->Resolve(new_mem);

                    for (UINT64 i = 0; i < this->size; i++)
                    {
                        new (&new_data[i]) T(old_data[i]);
                        old_data[i].~T();
                    }

                    this->allocator->Free(this->mem);
                    this->mem = new_mem;
                    this->capacity *= 2;
                }

                T* data = (T*)this->allocator->Resolve(this->mem);
                new (&data[this->size]) T(obj);
                this->size++;
            }

            void PopBack()
            {
                if (this->size == 0) return;

                this->size--;
                T* data = (T*)this->allocator->Resolve(this->mem);
                data[this->size].~T();
            }

            void Clear()
            {
                this->DestroyElements();
                this->size = 0;
            }

            void Reserve(UINT64 Size)
            {
                if (this->capacity < this->size + Size)
                {
                    UINT64 newCapacity = this->capacity + Size;

                    CytexLab::Interface::IAllocatorHandle new_mem;
                    this->allocator->Allocate(new_mem, sizeof(T) * newCapacity);

                    T* old_data = (T*)this->allocator->Resolve(this->mem);
                    T* new_data = (T*)this->allocator->Resolve(new_mem);

                    for (UINT64 i = 0; i < this->size; i++)
                    {
                        new (&new_data[i]) T(old_data[i]);
                        old_data[i].~T();
                    }

                    this->allocator->Free(this->mem);
                    this->mem = new_mem;
                    this->capacity = newCapacity;
                }
            }

            T& operator[](UINT64 Index)
            {
                T* data = (T*)this->allocator->Resolve(this->mem);
                return data[Index];
            }

            const T& operator[](UINT64 Index) const
            {
                T* data = (T*)this->allocator->Resolve(this->mem);
                return data[Index];
            }

            T* GetData()
            {
                return (T*)this->allocator->Resolve(this->mem);
            }

            const T* GetData() const
            {
                return (const T*)this->allocator->Resolve(this->mem);
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