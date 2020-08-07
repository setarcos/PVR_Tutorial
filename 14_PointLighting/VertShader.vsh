attribute highp   vec3  inVertex;
attribute mediump vec3  inTexColor;
attribute mediump vec3  inNormal;

uniform mediump mat4    MVPMatrix;
uniform mediump mat4    MVMatrix;
uniform mediump mat3    MVITMatrix;

varying mediump vec3    texture_or_color;
varying highp   vec3    transNormal;
varying highp   vec3    transPos;

void main(void)
{
    gl_Position = MVPMatrix * vec4(inVertex, 1.0);
    texture_or_color = inTexColor;

    transPos = vec3(MVMatrix * vec4(inVertex, 1.0));
    transNormal = normalize(MVITMatrix * inNormal);

}
