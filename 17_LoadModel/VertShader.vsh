#version 310 es

in highp   vec3  inVertex;
in mediump vec3  inNormal;
in mediump vec3  inTexColor;

uniform mediump mat4    MVPMatrix;
uniform mediump mat4    MVMatrix;
uniform mediump mat3    MVITMatrix;
uniform mediump int     IsSphere;

out mediump vec3    texture_or_color;
out highp   vec3    transNormal;
out highp   vec3    transPos;

void main(void)
{
    if (IsSphere == 1) {
        texture_or_color = vec3(0.8, 0.8, 0.8);
    } else {
        texture_or_color = inTexColor;
    }
    transNormal = normalize(MVITMatrix * inNormal);
    gl_Position = MVPMatrix * vec4(inVertex, 1.0);
    transPos = vec3(MVMatrix * vec4(inVertex, 1.0));
}
