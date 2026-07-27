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
        template <typename K, typename V>
        class Map
        {
        private:
            struct Item
            {
                K key;
                V value;
            };

            Vector<Item> container;

        public:
            Map(CytexLab::Interface::IAllocator* Allocator) : container(Allocator)
            {

            }

            ~Map()
            {

            }

            void Insert(const K& key, const V& value)
            {
                Item item = {key, value};
                this->container.PushBack(item);
            }

            BOOL Find(const K& key, V& out) const
            {
                for (UINT64 i = 0; i < this->container.GetSize(); i++)
                {
                    Item item = this->container[i];
                    if (item.key == key)
                    {
                        out = item.value;
                        return TRUE;
                    }
                }
                return FALSE;
            }

            BOOL Remove(const K& key)
            {
                for (UINT64 i = 0; i < this->container.GetSize(); i++)
                {
                    if (this->container[i].key == key)
                    {
                        this->container[i] = this->container[this->container.GetSize() - 1];
                        this->container.PopBack();
                        return TRUE;
                    }
                }
                return FALSE;
            }
        };
    }
}