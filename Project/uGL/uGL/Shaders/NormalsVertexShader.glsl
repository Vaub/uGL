#version 330 core

layout(location = 0) in vec4 positionIn;
layout(location = 1) in vec4 colorIn;
layout(location = 2) in vec2 texCoordIn;
layout(location = 3) in vec3 normalIn;

out Data {
  vec4 position;
  vec4 color;
  vec3 normal;
} vertexDataOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 cameraPosition;

void main() {
  gl_Position = proj * view * model * positionIn;

  vertexDataOut.position = proj * view * model * positionIn;
  vertexDataOut.color = colorIn;
  vertexDataOut.normal = normalize(mat3(transpose(inverse(model))) * normalIn);
}
