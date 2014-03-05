// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//
// Emulates a subset of the Win32 threading API as a layer on top of WinRT threadpools.
//
// Supported features:
//
//    - CreateThread (returns a standard Win32 handle which can be waited on, then closed)
//    - CREATE_SUSPENDED and ResumeThread
//    - Partial support for SetThreadPriority (see below)
//    - Sleep
//    - Thread local storage (TlsAlloc, TlsFree, TlsGetValue, TlsSetValue)
//
// Differences from Win32:
//
//    - If using TLS other than from this CreateThread emulation, call TlsShutdown before thread/task exit
//    - No ExitThread or TerminateThread (just return from the thread function to exit)
//    - No SuspendThread, so ResumeThread is only useful in combination with CREATE_SUSPENDED
//    - SetThreadPriority is only available while a thread is in CREATE_SUSPENDED state
//    - SetThreadPriority only supports three priority levels (negative, zero, or positive)
//    - No thread identifier APIs (GetThreadId, GetCurrentThreadId, OpenThread)
//    - No affinity APIs
//    - No GetExitCodeThread
//    - Failure cases return error codes but do not always call SetLastError

#pragma once

#include <windows.h>

#ifdef __cplusplus
//namespace ThreadEmulation
//{
extern "C" 
    {
#endif
    #ifndef CREATE_SUSPENDED
    #define CREATE_SUSPENDED 0x00000004
    #endif

    HANDLE WINAPI CreateThreadRT(_In_opt_ LPSECURITY_ATTRIBUTES unusedThreadAttributes, _In_ SIZE_T unusedStackSize, _In_ LPTHREAD_START_ROUTINE lpStartAddress, _In_opt_ LPVOID lpParameter, _In_ DWORD dwCreationFlags, _Out_opt_ LPDWORD unusedThreadId);
    DWORD WINAPI ResumeThreadRT(_In_ HANDLE hThread);
    BOOL WINAPI SetThreadPriorityRT(_In_ HANDLE hThread, _In_ int nPriority);
    
    VOID WINAPI SleepRT(_In_ DWORD dwMilliseconds);

    DWORD WINAPI TlsAllocRT();
    BOOL WINAPI TlsFreeRT(_In_ DWORD dwTlsIndex);
    LPVOID WINAPI TlsGetValueRT(_In_ DWORD dwTlsIndex);
    BOOL WINAPI TlsSetValueRT(_In_ DWORD dwTlsIndex, _In_opt_ LPVOID lpTlsValue);
    
    void WINAPI TlsShutdown();
#ifdef __cplusplus
    }
#endif
