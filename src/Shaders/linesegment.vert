#version 330 core

layout(location = 0) in vec4 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out float t;

void main()
{
	t = aPos.w;
	gl_Position = projection*view*model*vec4(aPos.xyz, 1.0);
}