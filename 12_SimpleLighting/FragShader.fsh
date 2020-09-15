uniform mediump sampler2D sTexture;

varying mediump vec3 texture_or_color;
varying mediump float brightness;

void main (void)
{
    if (texture_or_color.r > 1.0)
        gl_FragColor = texture2D(sTexture, texture_or_color.gb) * brightness;
    else
        gl_FragColor = vec4(texture_or_color * brightness, 1.0);
}
