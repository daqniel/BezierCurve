#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 axis;

void main()
{
	if(aPos.z != 0.0)
	{
		axis = vec3(0,0,1.0);
	}
	else if(aPos.y != 0.0)
	{
		axis = vec3(0, 1.0, 0);
	}
	else if(aPos.x != 0.0)
	{
		axis = vec3(1.0, 0, 0);
	}
	gl_Position = projection*view*model*vec4(aPos, 1.0);
}