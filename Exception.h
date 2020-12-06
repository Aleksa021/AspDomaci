#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
using namespace std;
class Error :public exception {
	Error(const char* msg) : exception(msg) {}
};
#endif // !EXCEPTION_H
