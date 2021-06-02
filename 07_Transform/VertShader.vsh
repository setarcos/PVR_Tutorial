#version 310 es
in highp vec4    inVertex;
in mediump vec3  inColor;
uniform mediump mat4    MVPMatrix;
out mediump vec3    fColor;
void main(void)
{
    gl_Position = MVPMatrix * inVertex;
    fColor = inColor;
}
