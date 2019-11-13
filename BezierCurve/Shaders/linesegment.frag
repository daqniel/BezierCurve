#version 330 core

out vec4 FragColor;

in float t;

void main()
{
	float s = 1-t;
	FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}