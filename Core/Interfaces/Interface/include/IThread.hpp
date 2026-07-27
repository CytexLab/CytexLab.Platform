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

namespace CytexLab
{
    namespace Interface
    {
        typedef UINT32 (*IThreadFunc)(LPVOID Arg);

        class IThread
        {
        public:
            virtual void Start() = 0;
            virtual void Join() = 0;
            virtual void Terminate() = 0;
            virtual UINT64 GetID() = 0;
            virtual void IsRunning(BOOL& Out) = 0;
        };
    }
}