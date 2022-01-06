#include "Test.h"

Test::Test() {
    cout << "Enter programm adress: " << endl;
    getline(wcin, this->adrs);
    cout << "Enter timing(ms): " << endl;
    cin >> this->timing;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));   
}

void Test::StartProcess() {
    PCTSTR s = adrs.c_str();
    CreateProcess(s, NULL, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
    GetExitCodeProcess(pi.hProcess, &state);
}

void Test::StartMonitor() {
    system("cls");
    CPUData.push_back(GetCpuUsage());
    cout << "CPU load: " << CPUData.back() << " %" << endl;
    cout << "==========" << endl;

    WSData.push_back(GetWorkingSetBt(pi.hProcess));
    cout << "Working set: " << WSData.back() << " bytes" << endl;
    PBData.push_back(GetPrivateBt(pi.hProcess));
    cout << "Private bytes: " << PBData.back() << " bytes" << endl;
    cout << "==========" << endl;

    GetProcessHandleCount(pi.hProcess, &hndlCnt);
    HCData.push_back(hndlCnt);
    cout << "Handle count: " << HCData.back() << endl;
    cout << "==========" << endl;
    Sleep(timing);
    GetExitCodeProcess(pi.hProcess, &state);
}

void Test::PrintToFile() {
    fstream f("base.csv", ios::out | ios::trunc);
    f << "Programm adress" << ",";
    for (int i = 0; i < adrs.size(); i++) {
        f << (char)adrs[i];
    }
    f << endl << "Time(ms)" << ",";
    for (int i = 0; i < CPUData.size(); i++) {
        f << timing * i << ",";
    }
    f << endl << "CPU(%)" << ",";
    for (int i = 0; i < CPUData.size(); i++) {
        f << CPUData[i] << ",";
    }
    f << endl << "Working Set(bytes)" << ",";
    for (int i = 0; i < WSData.size(); i++) {
        f << WSData[i] << ",";
    }
    f << endl << "Private Bytes(bytes)" << ",";
    for (int i = 0; i < PBData.size(); i++) {
        f << PBData[i] << ",";
    }
    f << endl << "Handle Count" << ",";
    for (int i = 0; i < HCData.size(); i++) {
        f << HCData[i] << ",";
    }
    f << endl;
    f.close();
}

int Test::GetCpuUsage() {
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

int Test::GetWorkingSetBt(HANDLE hprocess) {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(hprocess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    return pmc.WorkingSetSize;
}

int Test::GetPrivateBt(HANDLE hprocess) {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(hprocess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    return pmc.PrivateUsage;
}

DWORD Test::GetState() {
    return this->state;
}

Test::~Test() {
    adrs.clear();
    timing = 0;
    CPUData.clear();
    WSData.clear();
    PBData.clear();
    HCData.clear();
}