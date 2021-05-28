#version 310 es
layout(location = 0)in highp   vec3 inVertex;
layout(location = 1)in highp   vec3 inNormal;
layout(location = 2)in mediump vec2 inTexCoord;
layout(location = 3)in highp   vec4 inTangent;

layout(location = 0) out highp vec3 outWorldPos;
layout(location = 1) out mediump vec3 outNormal;
layout(location = 2) flat out mediump int outInstanceIndex;
layout(location = 3) out mediump vec2 outTexCoord;
layout(location = 4) out mediump vec3 outTangent;
layout(location = 5) out mediump vec3 outBitTangent;

uniform highp mat4 VPMatrix;
uniform highp vec3 camPos;

void main(void)
{
    outTexCoord = inTexCoord;
    // Scale 22.0 times
    highp vec4 posTmp = vec4(inVertex, 1.0) * vec4(22.0, 22.0, 22.0, 1.0);
    outNormal = normalize(inNormal);
    outTangent = inTangent.xyz;
    outBitTangent = cross(inNormal, inTangent.xyz) * inTangent.w;
    outWorldPos = posTmp.xyz;
    outInstanceIndex = gl_InstanceID;
    gl_Position = VPMatrix * posTmp;
}
