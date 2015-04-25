#version 330 core

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float shineFactor;
};

struct Light {
  vec3 position;
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

in vec4 position;
in vec4 color;
in vec2 texCoord;
in vec3 normal;

out vec4 colorOut;

uniform vec3 viewPosition;

uniform Material material;
uniform Light light;

uniform bool useTexture;
uniform sampler2D textureSampler;

void main() {
  vec3 ambient = light.ambient * material.ambient;

  vec3 N = normalize(normal);
  vec3 V = normalize(viewPosition - vec3(position));
  vec3 L = normalize(light.position - vec3(position));
  vec3 R = reflect(-L, N);

  float diffuse = max(dot(N, L), 0.0);
  float specular = pow(max(dot(V, R), 0.0), material.shineFactor);

  vec4 colorToAdd = vec4(1,1,1,1);
  if (useTexture) {
    colorToAdd = texture(textureSampler, texCoord);
  }

  colorOut = vec4(
    ambient +
    light.diffuse * (diffuse * material.diffuse)  +
    light.specular * (specular * material.specular),
    1.0) * colorToAdd;

}
