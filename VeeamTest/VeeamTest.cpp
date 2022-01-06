#include "Test.h"

int main() {
    Test test;
    test.StartProcess();

    while (test.GetState() != 0) {
        test.StartMonitor();
    }

    test.PrintToFile();
}
/*
C:\Program Files\Image-Line\FL Studio 20\FL.exe
*/