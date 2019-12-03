#version 410 core

layout(vertices = 9) out;

in vec4 worldPos_TCS[];
in float curvature_TCS[];
in vec4 normal_TCS[];

out vec4 worldPos_ES[];
out float curvature_TES[];
out vec4 normal_ES[];

uniform vec3 cameraPos;

void main() {
  worldPos_ES[gl_InvocationID] = worldPos_TCS[gl_InvocationID];
  normal_ES[gl_InvocationID] = normal_TCS[gl_InvocationID];
  curvature_TES[gl_InvocationID] = curvature_TCS[gl_InvocationID];

  if (gl_InvocationID == 0) {
    gl_TessLevelOuter[0] = 100;
    gl_TessLevelOuter[1] = 100;
    gl_TessLevelOuter[2] = 100;
    gl_TessLevelOuter[3] = 100;

    gl_TessLevelInner[0] = 100;
    gl_TessLevelInner[1] = 100;
  }

  //  float camToVertexDist0 = distance(cameraPos, worldPos_ES[0]);
  // float camToVertexDist1 = distance(cameraPos, worldPos_ES[0]);
  // float camToVertexDist2 = distance(cameraPos, worldPos_ES[0]);
}