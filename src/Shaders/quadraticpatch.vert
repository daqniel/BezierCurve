#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;

uniform mat4 model;

out vec3 worldPos_TCS;
out vec3 normal_TCS;
out float curvature_TCS;

uniform mat4 view;
uniform mat4 projection;

void main() {
  worldPos_TCS = (model * vec4(aPos, 1.0)).xyz;
  normal_TCS = (model * vec4(aNorm, 0.0)).xyz;
  normal_TCS = normalize(normal_TCS);
  gl_Position = vec4(aPos.xyz, 1.0);
}