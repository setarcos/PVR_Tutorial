#version 310 es
layout(location = 0) out mediump vec4 outColor;

layout(binding = 0) uniform mediump sampler2D albedoMap;
layout(binding = 1) uniform mediump sampler2D metallicRoughnessMap;
layout(binding = 2) uniform mediump sampler2D normalMap;
layout(binding = 3) uniform mediump sampler2D emissiveMap;

#define PI 3.1415926535897932384626433832795
#define ONE_OVER_PI (1.0 / 3.1415926535897932384626433832795)

layout(location = 0) in highp vec3 inWorldPos;
layout(location = 1) in mediump vec3 inNormal;
layout(location = 2) flat in mediump int inInstanceIndex;
layout(location = 3) in mediump vec2 inTexCoord;
layout(location = 4) in mediump vec3 inTangent;
layout(location = 5) in mediump vec3 inBitTangent;

mediump vec3 perturbNormal()
{
    // transform the tangent space normal into model space.
    mediump vec3 tangentNormal = texture(normalMap, inTexCoord).xyz * 2.0 - 1.0;
    mediump vec3 n = normalize(inNormal);
    mediump vec3 t = normalize(inTangent);
    mediump vec3 b = normalize(inBitTangent);
    return normalize(mat3(t, b, n) * tangentNormal);
}

void main (void)
{
    mediump vec3 lightDir = vec3(-1.0);
    mediump vec4 albedo = texture(albedoMap, inTexCoord);
    mediump vec3 N = perturbNormal();
    highp float brightness = max(dot(N, lightDir), 0.0) + 0.2;
    outColor = albedo * brightness;
}
