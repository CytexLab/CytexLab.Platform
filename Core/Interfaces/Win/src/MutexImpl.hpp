#pragma once

#include "IMutex.hpp"

class MutexImpl : public CytexLab::Interface::IMutex
{
private:
    HANDLE handle;

public:
    MutexImpl(HANDLE Handle);
    ~MutexImpl();

    HANDLE GetHandle();

    CytexLab::Interface::IMutexResult Lock() override;
    CytexLab::Interface::IMutexResult UnLock() override;
    CytexLab::Interface::IMutexResult TryLock(BOOL& Out) override;
};