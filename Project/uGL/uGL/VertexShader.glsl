#version 430

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec4 vertexColor;
in layout(location = 2) vec2 inTextureCoordinates;

out vec4 theColor;
out vec4 thePosition;

out vec3 light;

out vec2 outTextureCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	theColor = vertexColor;
	thePosition = proj * view * model * vec4(vertexPosition, 1.0);
	light = (view * model * vec4(vertexPosition, 1.0)).xyz;

	gl_Position = thePosition;

	outTextureCoordinates = inTextureCoordinates
}
