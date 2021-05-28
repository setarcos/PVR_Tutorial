#version 310 es

layout (binding = 9) uniform samplerCube skyboxMap;
layout (location = 0) out mediump vec4 outColor;
layout(location = 0) in mediump vec3 inRayDir;

void main()
{
	// Sample skybox cube map
	outColor = texture(skyboxMap, inRayDir);
}
