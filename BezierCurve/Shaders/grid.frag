#version 330 core

out vec4 FragColor;

in vec3 axis;

void main()
{
	if(axis.x != 0)
	{
		FragColor = vec4(1.0, 0, 0, 1.0);
	}
	else if(axis.y != 0)
	{
		FragColor = vec4(0, 0, 1.0, 1.0);
	}
	else
	{
		FragColor = vec4(0, .5, 0, 1.0);
	}

}