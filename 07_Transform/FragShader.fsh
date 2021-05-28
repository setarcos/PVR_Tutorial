#version 310 es
in mediump vec2 TexCoord;
uniform mediump sampler2D sTexture;
out mediump vec4 outColor;
void main (void)
{
    outColor = texture2D(sTexture, TexCoord);
}
