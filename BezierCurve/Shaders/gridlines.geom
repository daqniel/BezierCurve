#version 330 core

layout (points) in;
layout (line_strip, max_vertices = 6) out;

in vec3 axis[];
out vec3 gAxis;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 pos;
uniform vec3 neg;

void main()
{
		gAxis = axis[0];
		vec4 point = gl_in[0].gl_Position;
		if(axis[0] == vec3(0, 1.0, 0))
		{
			gl_Position = point + vec4(pos.x,0,0, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = point + vec4(neg.x,0,0, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();	
			gl_Position = projection*view*model*point;
			EmitVertex();
			gl_Position = point + vec4(0,0,pos.z, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = point + vec4(0,0,neg.z, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();	
		}
		else if(axis[0] == vec3(1.0, 0, 0))
		{
			gl_Position = point + vec4(0,pos.y,0,0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = point + vec4(0,neg.y,0,0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = projection*view*model*point;
			EmitVertex();
			gl_Position = point + vec4(0,0,pos.z, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = point + vec4(0,0,neg.z, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();	
		}
		else if(axis[0] == vec3(0, 0, 1.0))
		{
			gl_Position = point + vec4(0,pos.y,0,0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = point + vec4(0,neg.y,0,0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = projection*view*model*point;
			EmitVertex();
			gl_Position = point + vec4(pos.x,0,0, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();
			gl_Position = point + vec4(neg.x,0,0, 0);
			gl_Position = projection*view*model*gl_Position;
			EmitVertex();	
		}
	
		EndPrimitive();
}
