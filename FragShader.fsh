uniform mediump sampler2D sTexture;
uniform mediump samplerCube sCubeMap;
uniform mediump vec3 LightPosition;
uniform mediump vec4 LightColor;

varying mediump vec3 texture_or_color;
varying highp   vec3 transNormal;
varying highp   vec3 transPos;
varying highp   vec3 worldPos;
varying highp   vec3 reflectDir;

const highp float shininess = 80.0;

void main (void)
{
    // Diffuse light
    mediump vec3 lightDirection = LightPosition - transPos;
    highp float distance = length(lightDirection);
    lightDirection = normalize(lightDirection);
    highp float brightness = max(dot(transNormal, lightDirection), 0.0);

    mediump vec3 ambient = vec3(0.2);
    mediump vec3 diffuse = LightColor.rgb * brightness * 2.0
       / (distance * distance) + ambient;

    // Specular light
    mediump vec3 specular;
    highp vec3 eyeDirection = normalize(-transPos);
    if (brightness > 0.0) {
        highp vec3 halfVector = normalize(lightDirection + eyeDirection);
        highp float spec = pow(max(dot(transNormal, halfVector), 0.0), shininess);
        specular = spec * LightColor.rgb;
    } else {
        specular = vec3(0.0);
    }
    if (texture_or_color.r > 1.0) {
        if (texture_or_color.r == 2.0)
            gl_FragColor = texture2D(sTexture, vec2(texture_or_color.g, texture_or_color.b)) * vec4(diffuse, 1.0) + vec4(specular, 0.0);
        if (texture_or_color.r == 3.0)
            gl_FragColor = textureCube(sCubeMap, normalize(worldPos));
        if (texture_or_color.r == 4.0)
            gl_FragColor = textureCube(sCubeMap, reflectDir) + vec4(specular, 0.0);
    }
    else
        gl_FragColor = vec4(texture_or_color * diffuse + specular, 1.0);
}
