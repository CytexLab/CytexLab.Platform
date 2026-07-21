/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#pragma once

#include "Types.hpp"

namespace CytexLab
{
    namespace Interface
    {
        class IRenderWindow
        {
        public:
            virtual void SwapBuffers() = 0;
            virtual void loadOpenGL33() = 0;
        };
    }
}