#version 330 core

layout(location = 0) in vec4 positionIn;

out vec3 texCoord;

uniform mat4 proj;
uniform mat4 view;

void main()
{
    gl_Position = proj * mat4(mat3(view)) * positionIn;
    texCoord = vec3(positionIn);
}
