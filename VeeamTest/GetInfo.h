#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <Psapi.h>

using namespace std;

int GetCpuUsage() {
    static ULARGE_INTEGER TimeIdle, TimeKernel, TimeUser;
    FILETIME Idle, Kernel, User;
    ULARGE_INTEGER uIdle, uKernel, uUser;
    GetSystemTimes(&Idle, &Kernel, &User);
    memcpy(&uIdle, &Idle, sizeof(FILETIME));
    memcpy(&uKernel, &Kernel, sizeof(FILETIME));
    memcpy(&uUser, &User, sizeof(FILETIME));
    int t;
    t = (((((uKernel.QuadPart - TimeKernel.QuadPart) + (uUser.QuadPart - TimeUser.QuadPart)) -
        (uIdle.QuadPart - TimeIdle.QuadPart)) * (100)) / ((uKernel.QuadPart -
            TimeKernel.QuadPart) + (uUser.QuadPart - TimeUser.QuadPart)));
    TimeIdle.QuadPart = uIdle.QuadPart;
    TimeUser.QuadPart = uUser.QuadPart;
    TimeKernel.QuadPart = uKernel.QuadPart;
    return t;
}

int GetWorkingSetBt(HANDLE hprocess) {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(hprocess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    return pmc.WorkingSetSize;
}

int GetPrivateBt(HANDLE hprocess) {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(hprocess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    return pmc.PrivateUsage;
}