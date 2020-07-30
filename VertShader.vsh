attribute highp vec4    inVertex;
attribute mediump vec3  inTexColor;
uniform mediump mat4    MVPMatrix;
varying mediump vec3    texture_or_color;
void main(void)
{
    gl_Position = MVPMatrix * inVertex;
    texture_or_color = inTexColor;
}
