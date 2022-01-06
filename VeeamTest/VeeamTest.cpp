#include "Test.h"

int main() {
	try {
		Test test;
		test.StartProcess();

		while (test.GetState() != 0) {
			test.StartMonitor();
		}

		test.PrintToFile();
	}
	catch (MyException& exception) {
		cout << "Exception occurred : " << exception.what() << "\n";
	}
	catch (exception& exception) {
		cout << "Some other exception occurred : " << exception.what() << "\n";
	}
}
/*
C:\Program Files\Image-Line\FL Studio 20\FL.exe
*/