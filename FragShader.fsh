uniform mediump sampler2D sTexture;
uniform mediump vec3 LightPosition;
uniform mediump vec4 LightColor;

varying mediump vec3 texture_or_color;
varying highp   vec3 transNormal;
varying highp   vec3 transPos;

const highp float shininess = 20.0;

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
        gl_FragColor = texture2D(sTexture, vec2(texture_or_color.g, texture_or_color.b)) * diffuse + specular;
    else
        gl_FragColor = vec4(texture_or_color, 1.0) * diffuse + specular;
}
