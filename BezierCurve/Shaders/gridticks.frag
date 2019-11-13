#version 330 core

out vec4 FragColor;

in vec3 gAxis;

void main()
{
	FragColor = vec4(gAxis.xzy, 1.0);
}