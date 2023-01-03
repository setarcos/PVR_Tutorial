#version 310 es
uniform mediump sampler2D sTexture;
uniform mediump vec3 LightPosition;
uniform mediump vec4 LightColor;

in mediump vec3 texture_or_color;
in highp   vec3 transNormal;
in highp   vec3 transPos;

out mediump vec4 outColor;

const highp float shininess = 80.0;

void main (void)
{
    // Diffuse light
    mediump vec3 lightDirection = normalize(LightPosition - transPos);
    highp float brightness = max(dot(transNormal, lightDirection), 0.0);
    mediump vec4 diffuse = LightColor * brightness;

    // Specular light
    mediump vec4 specular;
    if (brightness > 0.0) {
        highp vec3 eyeDirection = normalize(-transPos);
        highp vec3 halfVector = normalize(lightDirection + eyeDirection);
        highp float spec = pow(max(dot(transNormal, halfVector), 0.0), shininess);
        specular = spec * LightColor;
    } else {
        specular = vec4(0.0);
    }
    if (texture_or_color.r > 1.0)
        outColor = texture(sTexture, texture_or_color.gb) * diffuse + specular;
    else
        outColor = vec4(texture_or_color, 1.0) * diffuse + specular;
}
