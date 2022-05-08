#version 310 es
uniform mediump sampler2D sTexture;
in mediump vec2 TexCoord;
out mediump vec4 outColor;
void main (void)
{
    outColor = texture(sTexture, TexCoord);
}
