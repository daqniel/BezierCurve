#version 330 core

out vec4 FragColor;

in float t;
uniform vec3 control_color;

void main()
{
//	if(t >= 1)
	//{
		FragColor = vec4(control_color, 1.0);
//	}
//	else
	//{
		//FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	//}
}