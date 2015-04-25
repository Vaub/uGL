#version 330 core

in layout(location = 0) vec4 positionIn;
in layout(location = 1) vec4 colorIn;
in layout(location = 2) vec2 texCoordIn;
in layout(location = 3) vec3 normalIn;

out vec4 position;
out vec4 color;
out vec2 texCoord;
out vec3 normal;

out vec3 viewPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform mat3 normalMatrix;

void main() {

  position =  model * positionIn;
  gl_Position = proj * view * model * positionIn;

  color = colorIn;
  texCoord = texCoordIn;
  normal = normalize(normalMatrix * normalIn);
}
