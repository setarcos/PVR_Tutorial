#version 310 es
uniform mediump sampler2D sTexture;
uniform mediump samplerCube sCubeMap;

in mediump vec3 texture_or_color;
in highp   vec3 worldPos;

out mediump vec4 outColor;

void main (void)
{
    if (texture_or_color.r > 1.0) {
        if (texture_or_color.r < 2.5)
            outColor = texture(sTexture, texture_or_color.gb);
        else
            outColor = textureCube(sCubeMap, normalize(worldPos));
    } else
        outColor = vec4(texture_or_color, 1.0);
}
