#version 410 core
vec3 bezier2(vec3 a, vec3 b, float t) { return mix(a, b, t); }
vec3 bezier3(vec3 a, vec3 b, vec3 c, float t) {
  return mix(bezier2(a, b, t), bezier2(b, c, t), t);
}
layout(quads, equal_spacing, ccw) in;

in vec4 worldPos_ES[];
in float curvature_TES[];
in vec3 normal_ES[];

out vec3 fragPos;
out vec3 fragNorm;
out float curvature;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec3 duBezier3(float u, float v) {
  vec3 uCurve[3];
  uCurve[0] =
      bezier3(worldPos_ES[0].xyz, worldPos_ES[3].xyz, worldPos_ES[6].xyz, v);
  uCurve[1] =
      bezier3(worldPos_ES[1].xyz, worldPos_ES[4].xyz, worldPos_ES[7].xyz, v);
  uCurve[2] =
      bezier3(worldPos_ES[2].xyz, worldPos_ES[5].xyz, worldPos_ES[8].xyz, v);

  float s = 1 - v;
  return 2 * s * (uCurve[1] - uCurve[0]) + 2 * v * (uCurve[2] - uCurve[1]);
}

vec3 dvBezier3(float u, float v) {
  vec3 vCurve[3];
  vCurve[0] =
      bezier3(worldPos_ES[0].xyz, worldPos_ES[1].xyz, worldPos_ES[2].xyz, u);
  vCurve[1] =
      bezier3(worldPos_ES[3].xyz, worldPos_ES[4].xyz, worldPos_ES[5].xyz, u);
  vCurve[2] =
      bezier3(worldPos_ES[6].xyz, worldPos_ES[7].xyz, worldPos_ES[8].xyz, u);

  float s = 1 - u;
  return 2 * s * (vCurve[1] - vCurve[0]) + 2 * u * (vCurve[2] - vCurve[1]);
}

void main() {

  float u = gl_TessCoord.x;
  float v = gl_TessCoord.y;

  vec3 newquadratic[3];
  newquadratic[0] =
      bezier3(worldPos_ES[0].xyz, worldPos_ES[1].xyz, worldPos_ES[2].xyz, u);
  newquadratic[1] =
      bezier3(worldPos_ES[3].xyz, worldPos_ES[4].xyz, worldPos_ES[5].xyz, u);
  newquadratic[2] =
      bezier3(worldPos_ES[6].xyz, worldPos_ES[7].xyz, worldPos_ES[8].xyz, u);

  vec3 worldPos = bezier3(newquadratic[0], newquadratic[1], newquadratic[2], v);

  newquadratic[0] =
      bezier3(normal_ES[0].xyz, normal_ES[1].xyz, normal_ES[2].xyz, u);
  newquadratic[1] =
      bezier3(normal_ES[3].xyz, normal_ES[4].xyz, normal_ES[5].xyz, u);
  newquadratic[2] =
      bezier3(normal_ES[6].xyz, normal_ES[7].xyz, normal_ES[8].xyz, u);

  vec3 normal = vec3(0);
  normal = bezier3(newquadratic[0], newquadratic[1], newquadratic[2], v);

  normal = cross(duBezier3(u, v), dvBezier3(u, v));
  fragNorm = normalize(normal);

  //       curvature_TES[0] * w3 + curvature_TES[6] * u3 + curvature_TES[9]
  //       * v3
  //       + curvature_TES[1] * 3.0 * w2 * u + curvature_TES[3] * 3.0 * w *
  //       u2 + curvature_TES[2] * 3.0 * w2 * v + curvature_TES[7] * 3.0 *
  //       u2 * v + curvature_TES[5] * 3.0 * w * v2 + curvature_TES[8] * 3.0
  //       * u * v2 + +curvature_TES[4] * 6.0 * w * u * v;

  vec3 worldPosXYZ = worldPos.xyz;
  fragPos = worldPosXYZ;

  gl_Position = projection * view * vec4(worldPosXYZ, 1.0);
}