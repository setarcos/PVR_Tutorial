#version 310 es
in highp vec4    myVertex;
void main(void)
{
    gl_Position = myVertex;
}
