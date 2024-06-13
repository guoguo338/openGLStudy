#version 410 core

in vec3 aPos;
in vec3 aColor;

uniform float time;
uniform float speed;
out vec3 color;

void main()
{
    float dx = 0.3;
    float offsetX = sin(time * speed) * dx;
    gl_Position = vec4(aPos.x + offsetX, aPos.y, aPos.z, 1.0);
    color = aColor;
}