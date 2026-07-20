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