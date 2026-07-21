/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "SystemImpl.hpp"
#include "WindowImpl.hpp"
#include "WinImports.hpp"
#include "Placement.hpp"

INT64 WndProc(HANDLE hwnd, UINT32 msg, UINT64 wParam, INT64 lParam)
{
    if (msg == WM_CLOSE || msg == WM_DESTROY)
    {
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hwnd, msg, wParam, lParam);
}

void SystemImpl::CreateWindow(CytexLab::Interface::IWindow *&Out, LPCECHAR Title, UINT64 x, UINT64 y, UINT64 Width, UINT64 Height)
{
    if (!Title)
        ::ExitProcess(-1);

    WCHAR titleBuf[256];
    Unicode::ConvertStringResult convert_result = Unicode::ToUTF16String(Title, titleBuf);

    if (!convert_result.Success)
        ::ExitProcess(-1);

    static BOOL registered = FALSE;
    if (!registered)
    {
        WNDCLASSEXW wc = {};
        wc.cbSize = sizeof(wc);
        wc.lpfnWndProc = WndProc;
        wc.hInstance = ::GetModuleHandleW(NULLPTR);
        wc.lpszClassName = L"CytexLabWindow";
        wc.hCursor = ::LoadCursorW(NULLPTR, IDC_ARROW);

        UINT16 atom = ::RegisterClassExW(&wc);

        if (atom == 0)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        registered = TRUE;
    }

    HANDLE hwnd = ::CreateWindowExW(
        0,
        L"CytexLabWindow",
        titleBuf,
        WS_OVERLAPPEDWINDOW,
        (INT32)x, (INT32)y,
        (INT32)Width, (INT32)Height,
        NULLPTR, NULLPTR,
        ::GetModuleHandleW(NULLPTR),
        NULLPTR
    );

    if (!hwnd)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }


    ::ShowWindow(hwnd, SW_SHOW);
    ::UpdateWindow(hwnd);

    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(WindowImpl));
    if (!mem)
        ::ExitProcess(-1);

    WindowImpl* wi = new (mem) WindowImpl(hwnd, Width, Height);

    Out = (CytexLab::Interface::IWindow*) wi;
}

void SystemImpl::DestroyWindow(CytexLab::Interface::IWindow *Window)
{
    if (!Window)
        ::ExitProcess(-1);

    WindowImpl* wi = (WindowImpl*) Window;

    HANDLE hwnd = wi->GetHandle();

    ::DestroyWindow(hwnd);

    HANDLE heap = ::GetProcessHeap();
    BOOL result = ::HeapFree(heap, 0, wi);

    if (!result)
        ::ExitProcess(-1);
}