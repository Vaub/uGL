#version 330 core

in Data
{
  vec4 color;
} geoDataOut;

out vec4 colorOut;

void main()
{
  colorOut = geoDataOut.color;
}
