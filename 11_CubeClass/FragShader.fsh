#version 310 es
uniform mediump sampler2D sTexture;
in mediump vec3 texture_or_color;
out mediump vec4 outColor;
void main (void)
{
    if (texture_or_color.r > 1.0)
        outColor = texture2D(sTexture, texture_or_color.gb);
    else
        outColor = vec4(texture_or_color, 1.0);
}
