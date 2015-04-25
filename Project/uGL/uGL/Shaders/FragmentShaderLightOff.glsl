#version 330 core

in vec4 position;
in vec4 color;

in vec3 viewPosition;

const vec3 lightPosEc = vec3(-5.0,-5.0,10.0);
const vec3 lightColor = vec3(1.0,1.0,1.0);

out vec4 colorOut;

void main()
{
  vec3 X = dFdx(vec3(position));
  vec3 Y = dFdy(vec3(position));
  vec3 normal=normalize(cross(X,Y));

  vec3 lightDirection = normalize(lightPosEc - viewPosition);

  float light = max(0.0, dot(lightDirection, normal));

	colorOut = vec4(normal, 1.0);
	colorOut = vec4(light * lightColor * vec3(color), 1.0);
}
