#version 310 es
in highp vec4    inVertex;
in mediump vec3  inTexColor;
uniform mediump mat4    MVPMatrix;
out mediump vec3    texture_or_color;
void main(void)
{
    gl_Position = MVPMatrix * inVertex;
    texture_or_color = inTexColor;
}
