// a basic shader
// fragment shader
#version 130

out vec4 vFragColor;

uniform vec4 vColor;

void main(void)
{
  vFragColor = vColor;
}

// EOF
