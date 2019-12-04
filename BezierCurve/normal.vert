#version 330 core

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec3 aNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;

void main()
{
	normal = (model*vec4(aNorm, 0.0)).xyz;
	normal = normalize(normal);
	gl_Position = model*vec4(aPos.xyz, 1.0);
}