#version 310 es
in highp vec4    myVertex;
uniform mediump mat4    myPVMMatrix;
void main(void)
{
    gl_Position = myPVMMatrix * myVertex;
}
