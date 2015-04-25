#version 330 core

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float shineFactor;
};

struct DirLight {
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct Spotlight {
  vec3 position;
  vec3 direction;

  float cutOff;
  float outerCutOff;

  vec3 attenuation;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

#define NB_OF_LIGHTS 3

in vec4 position;
in vec4 color;
in vec2 texCoord;
in vec3 normal;

out vec4 colorOut;

uniform vec3 viewPosition;

uniform Material material;

uniform DirLight dirLight;
uniform Spotlight spotlights[NB_OF_LIGHTS];

uniform bool useTexture;
uniform sampler2D textureSampler;

vec3 CalculateDirLight(DirLight light, vec3 N, vec3 V);
vec3 CalculateSpotlight(Spotlight light, vec3 N, vec3 V, vec3 fragPos);

void main() {
  //vec3 ambient = light.ambient * material.ambient;

  vec3 N = normalize(normal);
  vec3 V = normalize(viewPosition - vec3(position));

  vec3 colorResult = CalculateDirLight(dirLight, N, V);
  for (int i = 0; i < NB_OF_LIGHTS; i++) {
    colorResult += CalculateSpotlight(spotlights[i], N, V, vec3(position));
  }

  colorOut = vec4(colorResult, 1.0);
}

vec3 CalculateDirLight(DirLight light, vec3 N, vec3 V)
{
  vec3 L = normalize(-light.direction);
  vec3 R = reflect(-L, N);

  float diffuse = max(dot(N, L), 0.0);
  float specular = pow(max(dot(V, R), 0.0), material.shineFactor);

  vec3 colorAmb = vec3(1,1,1);
  vec3 colorDif = vec3(1,1,1);
  vec3 colorSpec = vec3(1,1,1);
  if (useTexture) {
    colorAmb = vec3(texture(textureSampler, texCoord));
    colorDif = vec3(texture(textureSampler, texCoord));
    colorSpec = vec3(texture(textureSampler, texCoord));
  }

  return (light.ambient * colorAmb +
    light.diffuse * diffuse * colorDif +
    light.specular * specular * colorSpec);
}

vec3 CalculateSpotlight(Spotlight light, vec3 N, vec3 V, vec3 fragPos) {
  vec3 L = normalize(light.position - fragPos);
  vec3 R = reflect(-light.direction, N);

  float diffuseFactor = max(dot(N, L), 0.0);
  float specularFactor = pow(max(dot(V, R), 0.0), material.shineFactor);

  vec3 colorAmb = vec3(1,1,1);
  vec3 colorDif = vec3(1,1,1);
  vec3 colorSpec = vec3(1,1,1);
  if (useTexture) {
    colorAmb = vec3(texture(textureSampler, texCoord));
    colorDif = vec3(texture(textureSampler, texCoord));
    colorSpec = vec3(texture(textureSampler, texCoord));
  }

  vec3 ambient = light.ambient * colorAmb;
  vec3 diffuse = light.diffuse * diffuseFactor * colorDif;
  vec3 specular = light.specular * specularFactor * colorSpec;

  // edges
  float theta = dot(L, normalize(-light.direction));
  float epsilon = (light.cutOff - light.outerCutOff);
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
  diffuse  *= intensity;
  specular *= intensity;

  // intensity
  float distance    = length(light.position - fragPos);
  float attenuation = 1.0 / (light.attenuation.x + light.attenuation.y * distance + light.attenuation.z * (distance * distance));
  ambient  *= attenuation;
  diffuse  *= attenuation;
  specular *= attenuation;

  return (ambient + diffuse + specular);
}
