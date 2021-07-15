#version 310 es
uniform mediump float value;
layout (location = 0) out mediump vec4 outColor;
void main()
{
    mediump vec3 color = vec3(0.0, 1.0, 0.0);

    if (gl_FragCoord.x < value)
        outColor = vec4(color, 0.5);
    else
        outColor = vec4(color * 0.5, 0.5);
}
