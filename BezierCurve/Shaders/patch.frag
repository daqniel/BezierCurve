#version 330 core

out vec4 FragColor;

in vec4 fragPos;

void main()
{
		FragColor = vec4(fragPos.xyz, 1.0);
		FragColor = vec4(1.0);
}