#pragma once

#include "ISystem.hpp"

namespace CytexLab
{
    namespace Interface
    {
        namespace Fabric
        {
            class WinFabric
            {
            public:
                static ISystem* Create();
                static void Destroy(ISystem* Interface);
            };
        }
    }
}