#version 330 core

layout (points) in;
layout (line_strip, max_vertices = 2) out;

in vec3 normal[];
out vec3 gAxis;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
		vec4 point = gl_in[0].gl_Position;

			gl_Position = vec4(0, 0, 0, 1.0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = vec4(point.xyz + normal[0], 1.0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
	
		EndPrimitive();
}
