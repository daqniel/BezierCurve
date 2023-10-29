#version 330 core

out vec4 FragColor;

in float level;
uniform float eval_level;
uniform vec3 control_color;

void main()
{
	if(level <= eval_level)
	{
		vec3 color = control_color-vec3(level)/8;
		FragColor = vec4(color, .6);
	}

	/*
	if(level == 0)
	{
		FragColor = vec4(1.0, 0, 0, 1.0);
	}
	else if(level == 1)
	{
		FragColor = vec4(0,1,0,1);
	}
	else if(level == 2)
	{
		FragColor = vec4(0,0,1,1);
	}
	*/
	else
	{
		discard;
	}
}