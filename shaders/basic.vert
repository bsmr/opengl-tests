// a basic shader
// Vertex Shader
#version 130

in vec4 vVertex;

void main(void)
{
  gl_Position = vVertex;
}

// EOF
