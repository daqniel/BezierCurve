#version 330 core

layout(location = 0) in vec4 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 fragPos;

void main()
{
	fragPos = model*vec4(aPos.xyz, 1.0);
	gl_Position = projection*view*fragPos;
}