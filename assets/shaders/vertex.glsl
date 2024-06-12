#version 410 core
in vec3 aColor;
in vec3 aPos;
out vec3 color;
uniform float time;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    color = aColor * (cos(time) + 1.0) / 2.0;
}