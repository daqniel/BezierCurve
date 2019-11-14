#version 330 core

out vec4 FragColor;

in float t;
uniform float evalpoint_time;

void main()
{
	float s = 1-t;
	if(t <= evalpoint_time)
	{
		FragColor = vec4(1.0, 1.0, 1.0, .6);
	}
	else
	{
		FragColor = vec4(.5, .5, .5, .6);
	}
}