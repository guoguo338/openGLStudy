#pragma once

#ifdef DEBUG
#define GL_CALL(x) do { \
    x; \
    GLenum error = glGetError(); \
    if (error != GL_NO_ERROR) { \
        std::cerr << "OpenGL Error: " << error << " at line " << __LINE__ << std::endl; \
        exit(1); \
    } \
} while (0)
#else
#define GL_CALL(func) func;
#endif

void checkError();