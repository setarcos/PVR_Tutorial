#include "Triangle.h"

Triangle::Triangle(void) : _vbo(0), _texture(0), _mvp(0),
    _position(glm::mat4(1.0f)), _rotation(glm::mat4(1.0f))
{
}

Triangle::~Triangle(void)
{
    // Release Vertex buffer object.
    if(_vbo) gl::DeleteBuffers(1, &_vbo);
    // Frees the texture
    if(_texture) gl::DeleteTextures(1, &_texture);
}

bool Triangle::Init(pvr::Shell* shell, uint32_t mvpLoc)
{
    GLfloat afVertices[] = { // Vertex 1
                            -0.4f, -0.4f, -0.0f,    // Position 1
                             0.0f, 0.0f,                    // Texture coodinate 1
                             // Vertex 2
                             0.4f, -0.4f, -0.0f,    // Position 2
                             1.0f, 0.0f,                    // Texture coodinate 2
                             // Vertex 3
                             0.0f,  0.4f, -0.0f,    // Position 3
                             0.5f, 1.0f,                    // Texture coodinate 3
                             };

    // Create VBO for the triangle from our data
    // Gen VBO
    gl::GenBuffers(1, &_vbo);

    // Bind the VBO
    gl::BindBuffer(GL_ARRAY_BUFFER, _vbo);

    // Set the buffer's data
    gl::BufferData(GL_ARRAY_BUFFER, 3 * 6 * sizeof(GLfloat), afVertices, GL_STATIC_DRAW);

    // Unbind the VBO
    gl::BindBuffer(GL_ARRAY_BUFFER, 0);

    // Load the diffuse texture map using PVR Utils
    _texture = pvr::utils::textureUpload(*shell, "Image.pvr", GL_TRUE);
    gl::BindTexture(GL_TEXTURE_2D, _texture);
    gl::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gl::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Save the MVP matrix location for later use
    _mvp = mvpLoc;

    return true;
}

void Triangle::Update(float angle)
{
    // Rotate along Y Axis
    _rotation *= glm::rotate(angle, glm::vec3(0, -1, 0));
}

void Triangle::Render(glm::mat4 view, glm::mat4 projection)
{
    unsigned int _stride = 5 * sizeof(GLfloat);
    // Pass the View Matrix to the shader.
    // Since we are not translating the triangle we do not need a Model Matrix.

    glm::mat4 model = _position * _rotation;

    gl::UniformMatrix4fv(_mvp, 1, GL_FALSE, glm::value_ptr(projection * view * model));

    // Bind the VBO
    gl::BindBuffer(GL_ARRAY_BUFFER, _vbo);

    gl::EnableVertexAttribArray(0);
    // Points to the position data
    gl::VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _stride, 0);
    gl::EnableVertexAttribArray(1);
    gl::VertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, _stride, (void *)(3 * sizeof(GLfloat)));
    gl::DrawArrays(GL_TRIANGLES, 0, 3);

    // Unbind the VBO
    gl::BindBuffer(GL_ARRAY_BUFFER, 0);
}

void Triangle::SetPosition(float x, float y, float z)
{
    _position = glm::translate(glm::vec3(x, y, z));
}
