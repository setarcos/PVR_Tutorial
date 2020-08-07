uniform mediump sampler2D sTexture;
varying mediump vec2 TexCoord;
void main (void)
{
    gl_FragColor = texture2D(sTexture, TexCoord);
}
