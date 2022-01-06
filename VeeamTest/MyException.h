#pragma once
#include <iostream>
#include <exception>

using namespace std;

class MyException : public exception {
private:
	string error;

public:
	MyException(std::string err) : error(err) {

	}

	const char* what() const noexcept {
		return error.c_str();
	}
};