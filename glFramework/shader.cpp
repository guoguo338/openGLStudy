#include "shader.h"
#include "../wrapper/checkError.h"

Shader::Shader(){}
Shader::~Shader(){}

void Shader::begin() {
    GL_CALL(glUseProgram(mProgram));
}

void Shader::end() {
    GL_CALL(glUseProgram(0));
}
