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

#include "Types.hpp"
#include "GLFunctions.hpp"

namespace CytexLab
{
    namespace Interface
    {
        class IRenderWindow
        {
        public:
            virtual void SwapBuffers() = 0;
            virtual void loadOpenGL33() = 0;
            virtual GLFunctions getOpenGL33() = 0;
        };
    }
}