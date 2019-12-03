#version 410 core

layout(triangles, equal_spacing, ccw) in;

in vec4 worldPos_ES[];
in float curvature_TES[];
in vec3 normal_ES[];

out vec3 fragPos;
out vec3 fragNorm;
out float curvature;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() {

  float u = gl_TessCoord.x;
  float v = gl_TessCoord.y;
  float w = gl_TessCoord.z;
  float u3 = pow(u, 3);
  float v3 = pow(v, 3);
  float w3 = pow(w, 3);
  float u2 = pow(u, 2);
  float v2 = pow(v, 2);
  float w2 = pow(w, 2);

  vec4 worldPos =
      worldPos_ES[0] * w3 + worldPos_ES[6] * u3 + worldPos_ES[9] * v3 +
      worldPos_ES[1] * 3.0 * w2 * u + worldPos_ES[3] * 3.0 * w * u2 +
      worldPos_ES[2] * 3.0 * w2 * v + worldPos_ES[7] * 3.0 * u2 * v +
      worldPos_ES[5] * 3.0 * w * v2 + worldPos_ES[8] * 3.0 * u * v2 +
      worldPos_ES[4] * 6.0 * w * u * v;

  vec3 normal = normal_ES[0] * w3 + normal_ES[6] * u3 + normal_ES[9] * v3 +
                normal_ES[1] * 3.0 * w2 * u + normal_ES[3] * 3.0 * w * u2 +
                normal_ES[2] * 3.0 * w2 * v + normal_ES[7] * 3.0 * u2 * v +
                normal_ES[5] * 3.0 * w * v2 + normal_ES[8] * 3.0 * u * v2 +
                normal_ES[4] * 6.0 * w * u * v;
  fragNorm = normal;

  curvature =
      curvature_TES[0] * w3 + curvature_TES[6] * u3 + curvature_TES[9] * v3 +
      curvature_TES[1] * 3.0 * w2 * u + curvature_TES[3] * 3.0 * w * u2 +
      curvature_TES[2] * 3.0 * w2 * v + curvature_TES[7] * 3.0 * u2 * v +
      curvature_TES[5] * 3.0 * w * v2 + curvature_TES[8] * 3.0 * u * v2 +
      +curvature_TES[4] * 6.0 * w * u * v;

  vec3 worldPosXYZ = worldPos.xyz;

  gl_Position = projection * view * vec4(worldPosXYZ, 1.0);
}