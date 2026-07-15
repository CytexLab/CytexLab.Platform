#include "SystemImpl.hpp"
#include "WinImports.hpp"
#include "WinFabric.hpp"
#include "Placement.hpp"

CytexLab::Interface::ISystem* CytexLab::Interface::Fabric::WinFabric::Create()
{
    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(SystemImpl));
    return (ISystem*)(new (mem) SystemImpl());
}

void CytexLab::Interface::Fabric::WinFabric::Destroy(CytexLab::Interface::ISystem* Interface)
{
    SystemImpl* si = (SystemImpl*) Interface;
    HANDLE heap = ::GetProcessHeap();
    ::HeapFree(heap, 0, si);
}