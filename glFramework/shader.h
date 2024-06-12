#pragma once

#include "core.h"
#include <string>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void begin(); // begin use shader
    void end(); // end use shadr

private:
    // shader program
    // type: compile link
    void checkShaderErrors(GLuint target, const std::string type);

public:
    GLuint mProgram { 0 };

};