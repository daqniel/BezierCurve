#version 330 core

layout (lines_adjacency) in;
layout (line_strip, max_vertices = 9) out;

struct deCastelData
{
	vec4 level1[3];
	vec4 level2[2];
	vec4 eval_point;
};

void main()
{
	vec4 controlPoints[4];

	controlPoints[0] = gl_in[0].gl_Position;
	controlPoints[1] = gl_in[1].gl_Position;
	controlPoints[2] = gl_in[2].gl_Position;
	controlPoints[3] = gl_in[3].gl_Position;

	for(int i = 0; i < 4; i++)
	{
		gl_Position = controlPoints[i];
		EmitVertex();
	}

	EndPrimitive();



	for(int i = 0; i < 3; i++)
	{
		gl_Position = controlPoints[i+1]/2 + controlPoints[i]/2;
		EmitVertex();
	}

	EndPrimitive();
}
