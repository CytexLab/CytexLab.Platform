#pragma once

#include "IThread.hpp"

class ThreadImpl : public CytexLab::Interface::IThread
{
private:
    HANDLE handle;
    UINT64 id;

public:
    ThreadImpl(HANDLE hThread, UINT64 id);
    ~ThreadImpl();

    HANDLE GetHandle();

    CytexLab::Interface::IThreadResult Start() override;
    CytexLab::Interface::IThreadResult Join() override;
    CytexLab::Interface::IThreadResult Terminate() override;
    CytexLab::Interface::IThreadResult IsRunning(BOOL& Out) override;
    UINT64 GetID() override;
};