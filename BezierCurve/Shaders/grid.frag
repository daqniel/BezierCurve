#version 330 core

out vec4 FragColor;

in vec3 axis;

void main()
{
	FragColor = vec4(axis.xzy, 1.0);
}