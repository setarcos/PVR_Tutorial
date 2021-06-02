#version 310 es
in mediump vec3 fColor;
out mediump vec4 outColor;
void main (void)
{
    outColor = vec4(fColor, 1.0);
}
