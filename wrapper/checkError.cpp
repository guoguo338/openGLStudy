//
// Created by ByteDance on 2024/6/11.
//
#include "checkError.h"
#include <iostream>
#include <glad/glad.h>
#include <assert.h>

using namespace std;

void checkError() {
    GLenum errorCode = glGetError();
    string error = "";
    if (errorCode != GL_NO_ERROR) {
        switch (errorCode) {
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY";
                break;
            default:
                error = "UNKNOWN";
                break;
        }
        cout << error << endl;

        assert(false);
    }
}