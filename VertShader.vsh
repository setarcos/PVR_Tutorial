attribute highp vec3    inVertex;
attribute mediump vec3  inTexColor;
attribute mediump vec3  inNormal;

uniform mediump mat4    MVPMatrix;
uniform mediump mat3    MVITMatrix;
uniform mediump vec3    LightDirection;

varying mediump vec3    texture_or_color;
varying mediump float   brightness;

void main(void)
{
    gl_Position = MVPMatrix * vec4(inVertex, 1.0);
    texture_or_color = inTexColor;

    mediump vec3 transNormal = normalize(MVITMatrix * inNormal);
    brightness = max(dot(transNormal, -LightDirection), 0.0);
}
