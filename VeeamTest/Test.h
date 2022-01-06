#pragma once
#include "MyException.h"
#include <Windows.h>
#include <string>
#include <Psapi.h>
#include <fstream>
#include <vector>

using namespace std;

class Test{
private:
    wstring adrs;
    int timing;
    vector <int> CPUData;
    vector <int> WSData;
    vector <int> PBData;
    vector <int> HCData;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD state;
    DWORD hndlCnt;
public:
    Test();
    void StartProcess();
    void StartMonitor();
    void PrintToFile();
    int GetCpuUsage();
    int GetWorkingSetBt(HANDLE hprocess);
    int GetPrivateBt(HANDLE hprocess);
    DWORD GetState();
    ~Test();
};

