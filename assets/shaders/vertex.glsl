#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

uniform float time;
uniform float speed;
out vec3 color;
out vec2 uv;

void main()
{
    float scale = 1.0 / time * 4.0;
    vec3 sPos = aPos * scale;
    gl_Position = vec4(sPos, 1.0);
    color = aColor;
    uv = aUV;
}