#version 310 es
in highp   vec3  inVertex;
in mediump vec3  inTexColor;
in mediump vec3  inNormal;

uniform mediump mat4    MVPMatrix;
uniform mediump mat4    MVMatrix;
uniform mediump mat4    MMatrix;
uniform mediump mat3    MVITMatrix;

out mediump vec3    texture_or_color;
out highp   vec3    transNormal;
out highp   vec3    transPos;
out highp   vec3    worldPos;

void main(void)
{
    gl_Position = MVPMatrix * vec4(inVertex, 1.0);
    texture_or_color = inTexColor;

    transPos = vec3(MVMatrix * vec4(inVertex, 1.0));
    transNormal = normalize(MVITMatrix * inNormal);
    worldPos = vec3(MMatrix * vec4(inVertex, 1.0));
}
