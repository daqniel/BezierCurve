#version 330 core

out vec4 FragColor;

in float t;

void main()
{
	float s = 1-t;
	FragColor = vec4(t, 0.0, s, 1.0);
}