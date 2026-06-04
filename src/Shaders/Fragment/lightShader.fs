#version 330 core
out vec4 FragColor;

uniform vec3 color;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    FragColor = vec4(color, 1.0);
}