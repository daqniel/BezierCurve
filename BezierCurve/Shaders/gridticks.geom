#version 330 core

layout (points) in;
layout (line_strip, max_vertices = 2) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 axis[];
out vec3 gAxis;

void main()
{
		gAxis = axis[0];
		vec4 point = gl_in[0].gl_Position;

		if(axis[0] == vec3(0, 1.0, 0))
		{
			gl_Position = point + vec4(.05,0,0, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = point + vec4(.05,0,0, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();	
			gl_Position = projection*view*model*point;
			EmitVertex();
			gl_Position = point + vec4(0,0,.05, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = point + vec4(0,0,.05, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();	
		}
		else if(axis[0] == vec3(1.0, 0, 0))
		{
			gl_Position = point + vec4(0,.05,0,0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = point + vec4(0,.05,0,0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = projection*view*model*point;
			EmitVertex();
			gl_Position = point + vec4(0,0,.05, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = point + vec4(0,0,.05, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();	
		}
		else if(axis[0] == vec3(0, 0, 1.0))
		{
			gl_Position = point + vec4(0,.05,0,0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = point + vec4(0,.05,0,0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = projection*view*model*point;
			EmitVertex();
			gl_Position = point + vec4(.05,0,0, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = point + vec4(.05,0,0, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();	
		}
	
		EndPrimitive();
}
