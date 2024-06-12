#pragma once
#include <iostream>
using namespace std;

#ifdef DEBUG
#define GL_CALL(x) x;checkError();
#else
#define GL_CALL(func) func;
#endif

void checkError();