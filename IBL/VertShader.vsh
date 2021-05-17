#version 310 es
layout(location = 0)in highp   vec3 inVertex;
layout(location = 1)in highp   vec3 inNormal;
layout(location = 2)in mediump vec2 inTexCoord;
layout(location = 3)in highp   vec4 inTangent;

layout(location = 0) out highp vec3 outWorldPos;
layout(location = 1) out mediump vec3 outNormal;
layout(location = 2) flat out mediump int outInstanceIndex;
layout(location = 3) out mediump vec2 outTexCoord;

uniform highp mat4 VPMatrix;
uniform highp vec3 camPos;

void main(void)
{
    outTexCoord = inTexCoord;
    highp vec4 posTmp = vec4(inVertex, 1.0) * vec4(22.0, 22.0, 22.0, 1.0);
    gl_Position = VPMatrix * posTmp;
}
