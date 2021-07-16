#version 310 es

out mediump vec2 TexCoord;

void main()
{

	const mediump vec3 positions[4]= vec3[]
	(
		vec3(-1.0f, 1.0f, 1.0f),// top left
		vec3(-1.0f, -1.0f, 1.0f),// bottom left
		vec3(1.0f, -1.0f, 1.0f),// bottom right
		vec3(1.0f, 1.0f, 1.0f)// top right
	);
    const mediump vec2 uv[4] = vec2[]
        (
         vec2(0.0f, 1.0f),
         vec2(0.0f, 0.0f),
         vec2(1.0f, 0.0f),
         vec2(1.0f, 1.0f)
        );
	gl_Position = vec4(positions[gl_VertexID], 1.0);
    TexCoord = uv[gl_VertexID];
}
