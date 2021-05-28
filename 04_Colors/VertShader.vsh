#version 310 es
in highp vec4    myVertex;
in mediump vec4  myColor;
uniform mediump mat4    myPVMMatrix;
out mediump vec4    fColor;
void main(void)
{
    gl_Position = myPVMMatrix * myVertex;
    fColor = myColor;
}
