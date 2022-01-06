#include "GetInfo.h"
#include <fstream>
#include <vector>

int main() {
    wstring adrs;
    int timing = 0;
    vector <int> CPUData;
    vector <int> WSData;
    vector <int> PBData;
    vector <int> HCData;

    cout << "Enter programm adress: " << endl;
    getline(wcin, adrs);
    cout << "Enter timing(ms): " << endl;
    cin >> timing;

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    fstream f("base.csv", ios::out | ios::trunc);

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    PCTSTR s = adrs.c_str();
    CreateProcess(s, NULL, NULL, NULL, false, 0, NULL, NULL, &si, &pi);

    DWORD hndlCnt = 0, state = 0;
    GetExitCodeProcess(pi.hProcess, &state);

    f << adrs.c_str() << endl;

    while (state != 0) {
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
    f << "Programm adress" << ",";
    for (int i = 0; i < adrs.size(); i++) {
        f << (char)adrs[i];
    }
    f << endl << "Time(ms)" << ",";
    for (int i = 0; i < CPUData.size(); i++) {
        f << timing * i << ",";
    }
    f << endl <<  "CPU(%)" << ",";
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
}
/*
L"C:\\Program Files/Google/Chrome/Application/chrome.exe"
C:\Program Files\Image-Line\FL Studio 20\FL.exe
*/