#version 330 core

out vec4 FragColor;

in vec3 fragPos;
in vec3 fragNorm;

in float curvature;
uniform float maxCurvature;
uniform float minCurvature;

void main() {
  FragColor = vec4(fragPos, 1.0);
  FragColor = vec4(fragNorm, 1.0);
  FragColor = vec4(.7, .7, .7, 1.0);
}