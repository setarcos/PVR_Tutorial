uniform mediump sampler2D sTexture;
varying mediump vec3 texture_or_color;
void main (void)
{
    if (texture_or_color.r > 1.0)
        gl_FragColor = texture2D(sTexture, texture_or_color.gb);
    else
        gl_FragColor = vec4(texture_or_color, 1.0);
}
