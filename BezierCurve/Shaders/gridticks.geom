#version 330 core

layout (points) in;
layout (line_strip, max_vertices = 2) out;

in vec3 axis[];
out vec3 gAxis;

void main()
{
		gAxis = axis[0];
		vec4 point = gl_in[0].gl_Position;
		if(axis[0] == vec3(0, 1.0, 0))
		{
		gl_Position = point + .1*vec4(1,0,0,0);
		EmitVertex();
		gl_Position = point - .1*vec4(1,0,0,0);
		EmitVertex();	
		}
		else
		{
		gl_Position = point + .1*vec4(0,1,0,0);
		EmitVertex();
		gl_Position = point - .1*vec4(0,1,0,0);
		EmitVertex();
		}
	
		EndPrimitive();
}
