#include "shader.h"
#include "../wrapper/checkError.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;

    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (ifstream::failure & e) {
        cout << "ERROR: Shader File Error: " << e.what() << endl;
    }

    // create shader program (vs、fs)
    GLuint vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vertexShaderSource = vertexCode.c_str();
    const char *fragmentShaderSource = fragmentCode.c_str();

    // input shader code
    GL_CALL(glShaderSource(vertex, 1, &vertexShaderSource, nullptr));
    GL_CALL(glShaderSource(fragment, 1, &fragmentShaderSource, nullptr));

    // compile shader code
    GL_CALL(glCompileShader(vertex));
    checkShaderErrors(vertex, "COMPILE");

    GL_CALL(glCompileShader(fragment));
    checkShaderErrors(fragment, "COMPILE");

    // create a program
    mProgram = glCreateProgram();

    // put the compiled result of vs & fs to program
    GL_CALL(glAttachShader(mProgram, vertex));
    GL_CALL(glAttachShader(mProgram, fragment));

    // execute program, and create the executable shader
    GL_CALL(glLinkProgram(mProgram));
    checkShaderErrors(mProgram, "LINK");

    // clean up
    GL_CALL(glDeleteShader(vertex));
    GL_CALL(glDeleteShader(fragment));
}

Shader::~Shader(){}

void Shader::begin() {
    GL_CALL(glUseProgram(mProgram));
}

void Shader::end() {
    GL_CALL(glUseProgram(0));
}

void Shader::checkShaderErrors(GLuint target, const std::string type) {
    int success = 0;
    char infoLog[1024];
    if (type == "COMPILE") {
        GL_CALL(glGetShaderiv(target, GL_COMPILE_STATUS, &success));
        if (!success) {
            GL_CALL(glGetShaderInfoLog(target, 1024, nullptr, infoLog));
            cout << "Error: SHADER COMPILE ERROR --VERTEX" << "\n" << infoLog << endl;
        }
    } else if (type == "LINK") {
        GL_CALL(glGetProgramiv(target, GL_LINK_STATUS, &success));
        if (!success) {
            GL_CALL(glGetProgramInfoLog(target, 1024, NULL, infoLog));
            cout << "Error: SHADER LINK ERROR " << "\n" << infoLog << endl;
        }
    } else {
        cout << "ERROR: Check shader errors Type is wrong" << endl;
    }
}

void Shader::setFloat(const std::string& name, float value) {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
    GL_CALL(glUniform1f(location, value));
}

void Shader::setVector3(const std::string& name, float x, float y, float z) {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
    GL_CALL(glUniform3f(location, x, y, z));
}

// overload
void Shader::setVector3(const std::string& name, const float* values) {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
    GL_CALL(glUniform3fv(location, 1, values));
}

void Shader::setInt(const std::string& name, int value) {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
    GL_CALL(glUniform1i(location, value));
}

void Shader::setMarix4x4(const std::string& name, glm::mat4 value) {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
    GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
}
