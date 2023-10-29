#version 330 core
#define M_PI 3.1415926535897932384626433832795
#define NUM_LIGHTS 2

struct Light {
  vec3 pos;
  vec3 intensity;
  vec3 ambient;
};

struct Material {
  vec3 diffuse;
  vec3 specular;

  float m;
};

out vec4 FragColor;

in vec3 fragPos;
in vec3 fragNorm;
in vec2 texCoords;

uniform vec3 cameraPos;

uniform Light lights[NUM_LIGHTS];
uniform Material material;

vec3 halfvector(vec3 viewDir, vec3 lightDir) {
  vec3 halfvect = normalize(lightDir + viewDir);
  return halfvect;
}

vec3 blinnphong(Light light, Material material, vec3 norm, vec3 lightDir,
                float lightDistance, vec3 viewDir) {
  vec3 color = vec3(0);
  color += material.diffuse * light.ambient;
  color += material.diffuse * max(dot(norm, lightDir), 0) * light.intensity;
  color += pow(max(dot(norm, halfvector(viewDir, lightDir)), 0.0), 1000);

  return color;
}

//-----------------------------------------------------------------------

void main() {
  Material testMaterial;
  testMaterial.diffuse = vec3(.7, .7, .7);
  testMaterial.specular = vec3(.6, .6, .6);

  vec3 viewDir = normalize(cameraPos - fragPos);
  vec3 color = vec3(0.0);
  for (int i = 0; i < NUM_LIGHTS; i++) {
    vec3 lightDir = lights[i].pos - fragPos;
    float lightDist = length(lightDir);
    lightDir = normalize(lightDir);
    color += blinnphong(lights[i], testMaterial, fragNorm, lightDir, lightDist,
                        viewDir);
  }

  FragColor = vec4(color, 1.0);
}
//-----------------------------------------------------------------------
