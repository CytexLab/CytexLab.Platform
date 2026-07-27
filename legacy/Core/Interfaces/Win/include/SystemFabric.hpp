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

#include "ISystem.hpp"

namespace CytexLab
{
    namespace Interface
    {
        namespace Fabric
        {
            class SystemFabric
            {
            public:
                static ISystem* Create();
                static void Destroy(ISystem* Interface);
            };
        }
    }
}