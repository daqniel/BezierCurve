#version 330 core

layout (points) in;
layout (line_strip, max_vertices = 7) out;

/*
FrenetFrame calculateFrame()
{
	vec3 gradient = normalize(gl_in[2].gl_Position - gl_in[1].gl_Position);
	vec3 nextgradient = normalize(gl_in[3].gl_Position - gl_in[2].gl_Position);

	vec3 gradientofgradient = normalize(nextgradient - gradient);

	FrenetFrame result;
	result.tangent = gradient;
	result.normal = gradientofgradient;
	result.binormal = cross(result.tangent, result.normal);

	return result;
}
*/

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

uniform vec3 tangent;
uniform vec3 normal;
uniform vec3 binormal;

void main()
{
//	FrenetFrame frame = calculateFrame();
	vec4 point = gl_in[0].gl_Position;

	gl_Position = projection*view*model*point;
	EmitVertex();

	gl_Position = point + vec4(0.1*tangent, 1.0);
	gl_Position = projection*view*model*gl_Position;
	EmitVertex();

	gl_Position = projection*view*model*point;
	EmitVertex();

	gl_Position = point + vec4(0.1*normal, 1.0);
	gl_Position = projection*view*model*gl_Position;
	EmitVertex();

	gl_Position = projection*view*model*point;
	EmitVertex();

	gl_Position = point + vec4(0.1*binormal, 1.0);
	gl_Position = projection*view*model*gl_Position;
	EmitVertex();

	EndPrimitive();
}
