#version 330 core

layout (points) in;
layout (line_strip, max_vertices = 10) out;


//FrenetFrame calculateFrame()
//{
//	vec3 gradient = normalize(gl_in[2].gl_Position - gl_in[1].gl_Position);
//	vec3 nextgradient = normalize(gl_in[3].gl_Position - gl_in[2].gl_Position);
//
//	vec3 gradientofgradient = normalize(nextgradient - gradient);
//
//	FrenetFrame result;
//	result.tangent = gradient;
//	result.normal = gradientofgradient;
//	result.binormal = cross(result.tangent, result.normal);
//
//	return result;
//}

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

uniform vec3 tangent;
uniform vec3 normal;
uniform vec3 binormal;

out vec4 color;

void main()
{
//	FrenetFrame frame = calculateFrame();
	vec4 point = gl_in[0].gl_Position;

	color = vec4(0.0);
	gl_Position = projection*view*model*point;
	EmitVertex();

	color = vec4(1.0, 0, 0, 1.0);
	gl_Position = point + vec4(tangent, 0.0)*.3;
	gl_Position = projection*view*model*gl_Position;
	EmitVertex();

	color = vec4(0.0);
	gl_Position = projection*view*model*point;
	EmitVertex();

	color = vec4(0.0, 1.0, 0.0, 1.0);
	gl_Position = point + vec4(normal, 0.0)*.3;
	gl_Position = projection*view*model*gl_Position;
	EmitVertex();

	color = vec4(0.0);
	gl_Position = projection*view*model*point;
	EmitVertex();

	color = vec4(0.0, 0.0, 1.0, 1.0);
	gl_Position = point + vec4(binormal, 0.0)*.3;
	gl_Position = projection*view*model*gl_Position;
	EmitVertex();

	EndPrimitive();
}
