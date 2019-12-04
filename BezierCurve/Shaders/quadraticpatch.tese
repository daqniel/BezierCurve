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

vec3 derivative(vec3 c[3], float t)
{
	return 2 * (1 - t) *  (c[1]- c[2]) + 2 * t * (c[2] - c[1]);
}

vec3 derivative2(vec3 c[3], float t)
{
	return 2*(c[2]-2*c[1]+c[0]);
}

void main() {

  float u = gl_TessCoord.x;
  float v = gl_TessCoord.y;

  vec3 vCurve[3];
  vec3 uCurve[3];

  vec3 dvCurve[3];
  vec3 duCurve[3];

  vec3 u1[3];
  vec3 u2[3];
  vec3 u3[3];
  vec3 u4[3];

  vCurve[0] =
      bezier3(worldPos_ES[0].xyz, worldPos_ES[1].xyz, worldPos_ES[2].xyz, u);
  vCurve[1] =
      bezier3(worldPos_ES[3].xyz, worldPos_ES[4].xyz, worldPos_ES[5].xyz, u);
  vCurve[2] =
      bezier3(worldPos_ES[6].xyz, worldPos_ES[7].xyz, worldPos_ES[8].xyz, u);

//	dvCurve = bezier2(worldPos_ES[0].xyz)


  vec3 worldPos = bezier3(vCurve[0], vCurve[1], vCurve[2], v);
	  
  uCurve[0] =
      bezier3(worldPos_ES[0].xyz, worldPos_ES[3].xyz, worldPos_ES[6].xyz, v);
  uCurve[1] =
      bezier3(worldPos_ES[1].xyz, worldPos_ES[4].xyz, worldPos_ES[7].xyz, v);
  uCurve[2] =
      bezier3(worldPos_ES[2].xyz, worldPos_ES[5].xyz, worldPos_ES[8].xyz, v);


	 
  vec3 dv = derivative(vCurve, v);
  vec3 du = derivative(uCurve, u);
  //vec3 dvv = derivative2(vCurve, v);
  //vec3 duu = derivative2(uCurve, u);

 vec3 normal = cross(dv, du);

  //float E = dot(du, du);
  //float F = dot(du, dv);
  //float G = dot(dv, dv);
	
//  float L = dot(derivative2() , normal);
  //float M = dot(derivative2())


  fragNorm = normalize(normal);

  vec3 worldPosXYZ = worldPos.xyz;
  fragPos = worldPosXYZ;

  gl_Position = projection * view * vec4(worldPosXYZ, 1.0);
}