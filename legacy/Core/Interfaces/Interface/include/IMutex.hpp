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

#include "Platform.hpp"

namespace CytexLab
{
    namespace Interface
    {
        class IMutex
        {
        public:
            virtual void Lock() = 0;
            virtual void UnLock() = 0;
            virtual void TryLock(BOOL& Out) = 0;
        };
    }
}