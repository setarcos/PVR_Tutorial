#include "Triangle.h"

Triangle::Triangle(void) : _vbo(0), _mvp(0), _x(0), _y(0), _z(0)
{
}

Triangle::~Triangle(void)
{
    // Release Vertex buffer object.
    if(_vbo) gl::DeleteBuffers(1, &_vbo);
}

bool Triangle::Init(pvr::Shell* shell, uint32_t mvpLoc)
{
    GLfloat afVertices[] = { // Vertex 1
                            -0.4f+_x, -0.4f+_y, -2.0f+_z,    // Position 1
                             // Vertex 2
                             0.4f+_x, -0.4f+_y, -2.0f+_z,    // Position 2
                             // Vertex 3
                             0.0f+_x,  0.4f+_y, -2.0f+_z,    // Position 3
                             };

    // Create VBO for the triangle from our data
    // Gen VBO
    gl::GenBuffers(1, &_vbo);

    // Bind the VBO
    gl::BindBuffer(GL_ARRAY_BUFFER, _vbo);

    // Set the buffer's data
    gl::BufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(GLfloat), afVertices, GL_STATIC_DRAW);

    // Unbind the VBO
    gl::BindBuffer(GL_ARRAY_BUFFER, 0);

    // Save the MVP matrix location for later use
    _mvp = mvpLoc;

    return true;
}

void Triangle::Render(glm::mat4 mVP)
{
    // Pass the View Matrix to the shader.
    // Since we are not translating the triangle we do not need a Model Matrix.
    gl::UniformMatrix4fv(_mvp, 1, GL_FALSE, glm::value_ptr(mVP));

    // Bind the VBO
    gl::BindBuffer(GL_ARRAY_BUFFER, _vbo);

    gl::EnableVertexAttribArray(0);
    // Points to the position data
    gl::VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    gl::DrawArrays(GL_TRIANGLES, 0, 3);

    // Unbind the VBO
    gl::BindBuffer(GL_ARRAY_BUFFER, 0);
}

void Triangle::SetPosition(float x, float y, float z)
{
     _x = x;
     _y = y;
     _z = z;
}
