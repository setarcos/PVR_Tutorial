#version 310 es
layout(location = 0) in highp vec3 inVertex;
uniform mediump vec2 Pos;

void main()
{
    const mediump vec3 position[4] = vec3[]
    (
        vec3(0.0f, 0.0f, 1.0f),
        vec3(0.0f, -0.1f, 1.0f),
        vec3(0.3f, -0.1f, 1.0f),
        vec3(0.3f, 0.0f, 1.0f)
    );
    gl_Position = vec4(position[gl_VertexID] + vec3(Pos.x, Pos.y, 0.0), 1.0);
}
