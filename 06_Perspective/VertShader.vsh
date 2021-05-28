#version 310 es
in highp vec4    inVertex;
in mediump vec2  inTexCoord;
uniform mediump mat4    MVPMatrix;
out mediump vec2    TexCoord;
void main(void)
{
    gl_Position = MVPMatrix * inVertex;
    TexCoord = inTexCoord;
}
