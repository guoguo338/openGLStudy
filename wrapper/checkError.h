#pragma once
#include <iostream>
using namespace std;

#ifdef DEBUG
#define GL_CALL(x) do { \
    x; \
    GLenum error = glGetError(); \
    if (error != GL_NO_ERROR) { \
        std::cerr << "OpenGL Error: " << " at line " << __LINE__ << ", error: " << std::showbase << std::hex <<  error << std::endl; \
        exit(1); \
    } \
} while (0)
#else
#define GL_CALL(func) func;
#endif

void checkError();