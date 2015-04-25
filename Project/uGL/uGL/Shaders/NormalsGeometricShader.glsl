#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in Data
{
  vec4 position;
  vec4 color;
  vec3 normal;
} vertexDataOut[3];

out Data
{
    vec4 color;
} geoDataOut;

void main()
{
    const vec4 red = vec4(0.8f, 0.0f, 0.0f, 1.0f);
    const vec4 orange = vec4(1.0f, 0.8f, 0.0f, 1.0f);

    for (int i = 0; i < 3; i++)
    {
        gl_Position = vertexDataOut[i].position;
        geoDataOut.color = red;
        EmitVertex();

        gl_Position = vertexDataOut[i].position + vec4(vertexDataOut[i].normal, 1.0f);
        geoDataOut.color = orange;
        EmitVertex();

        EndPrimitive();
    }
}
