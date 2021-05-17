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

void main (void)
{
    mediump vec4 albedo = texture(albedoMap, inTexCoord);
    outColor = albedo;
}
