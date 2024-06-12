#pragma once

#include "core.h"

class Shader {
public:
    Shader();
    ~Shader();

    void begin(); // begin use shader
    void end(); // end use shadr

private:
    GLuint mProgram { 0 };


};