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

#include "WindowImpl.hpp"
#include "WinImports.hpp"

WindowImpl::WindowImpl(HANDLE Window, UINT64 Width, UINT64 Height)
{
    this->hWindow = Window;
    this->isOpen = TRUE;
    this->width = Width;
    this->height = Height;
}

WindowImpl::~WindowImpl()
{

}

HANDLE WindowImpl::GetHandle()
{
    return this->hWindow;
}

void WindowImpl::Process()
{
    MSG msg;

    while (::PeekMessageW(&msg, NULLPTR, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT) {
            this->isOpen = FALSE;
            return;
        }

        ::TranslateMessage(&msg);
        ::DispatchMessageW(&msg);
    }
}

BOOL WindowImpl::IsOpen()
{
    return this->isOpen;
}

UINT64 WindowImpl::GetHeight()
{
    return this->height;
}

UINT64 WindowImpl::GetWidth()
{
    return this->width;
}