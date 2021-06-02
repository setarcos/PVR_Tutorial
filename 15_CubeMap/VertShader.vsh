#version 310 es
in highp vec3    inVertex;
in mediump vec3  inTexColor;
uniform mediump mat4    MVPMatrix;
uniform mediump mat4    MMatrix;
out mediump vec3    texture_or_color;
out highp   vec3    worldPos;
void main(void)
{
    gl_Position = MVPMatrix * vec4(inVertex, 1.0);
    texture_or_color = inTexColor;
    worldPos = vec3(MMatrix * vec4(inVertex, 1.0));
}
