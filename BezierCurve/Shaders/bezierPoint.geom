#version 330 core

layout (points) in;
layout (points, max_vertices = 1) out;

void main()
{
	controlPoints[0] = gl_in[0].gl_Position;
	EmitVertex();
	EndPrimitive();
}
