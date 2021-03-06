#version 140

in vec3 normal;
in vec4 position_vs;

uniform vec3 color;

void main(void)
{
  gl_FragColor = vec4(color, 1) * normalize(normal).z;
}
