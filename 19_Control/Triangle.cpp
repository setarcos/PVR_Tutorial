#include "Triangle.h"

Triangle::Triangle(void) : _vbo(0), _texture(0), _mvp(0), _mv(0), _mvit(0),
    _nVertex(0), _position(glm::mat4(1.0f)), _rotation(glm::mat4(1.0f))
{
}

Triangle::~Triangle(void)
{
    // Release Vertex buffer object.
    if(_vbo) gl::DeleteBuffers(1, &_vbo);
    // Frees the texture
    if(_texture) gl::DeleteTextures(1, &_texture);
}

bool Triangle::Init(pvr::Shell* shell, uint32_t* mvpLoc)
{
    GLfloat afVertices[] = { // Vertex 1
                            -0.4f, -0.4f, -0.0f,    // Position 1
                             2.0f, 0.0f, 0.0f,      // Texture coodinate 1
                             0.0f, 0.0f, 1.0f,      // Normal 1
                             // Vertex 2
                             0.4f, -0.4f, -0.0f,    // Position 2
                             2.0f, 1.0f, 0.0f,      // Texture coodinate 2
                             0.0f, 0.0f, 1.0f,      // Normal 2
                             // Vertex 3
                             0.0f,  0.4f, -0.0f,    // Position 3
                             2.0f, 0.5f, 1.0f,      // Texture coodinate 3
                             0.0f, 0.0f, 1.0f,      // Normal 3
                             //Vertex 1
                            -0.4f, -0.4f, -0.0f,    // Position 1
                             0.5f, 0.0f, 1.0f,      // Color 1
                             0.0f, 0.0f, -1.0f,      // Normal 1
                             // Vertex 3
                             0.0f,  0.4f, -0.0f,    // Position 3
                             0.5f, 0.0f, 1.0f,      // Color 3
                             0.0f, 0.0f, -1.0f,      // Normal 3
                             // Vertex 2
                             0.4f, -0.4f, -0.0f,    // Position 2
                             0.5f, 0.0f, 1.0f,      // Color 2
                             0.0f, 0.0f, -1.0f,      // Normal 2
                             };

    // Create VBO for the triangle from our data
    // Gen VBO
    gl::GenBuffers(1, &_vbo);

    // Bind the VBO
    gl::BindBuffer(GL_ARRAY_BUFFER, _vbo);

    // Set the buffer's data
    gl::BufferData(GL_ARRAY_BUFFER, 6 * 9 * sizeof(GLfloat), afVertices, GL_STATIC_DRAW);

    // Unbind the VBO
    gl::BindBuffer(GL_ARRAY_BUFFER, 0);

    // Load the diffuse texture map using PVR Utils
    _texture = pvr::utils::textureUpload(*shell, "Image.pvr", GL_TRUE);
    gl::BindTexture(GL_TEXTURE_2D, _texture);
    gl::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gl::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Save the MVP matrix location for later use
    _mvp = mvpLoc[0];
    _mv = mvpLoc[1];
    _mvit = mvpLoc[2];

    _nVertex = 6;

    return true;
}

void Triangle::Update(float angle)
{
    // Rotate along Y Axis
    _rotation *= glm::rotate(angle, glm::vec3(0, -1, 0));
}

void Triangle::Render(glm::mat4 view, glm::mat4 projection)
{
    unsigned int _stride = 9 * sizeof(GLfloat);

    glm::mat4 model = _position * _rotation;

    glm::mat4 modelViewProj = projection * view * model;
    gl::UniformMatrix4fv(_mvp, 1, GL_FALSE, glm::value_ptr(modelViewProj));
    glm::mat4 modelView = view * model;
    gl::UniformMatrix4fv(_mv, 1, GL_FALSE, glm::value_ptr(modelView));
    glm::mat3 modelViewIT = glm::inverseTranspose(modelView);
    gl::UniformMatrix3fv(_mvit, 1, GL_FALSE, glm::value_ptr(modelViewIT));

    // Bind the VBO
    gl::BindBuffer(GL_ARRAY_BUFFER, _vbo);

    gl::EnableVertexAttribArray(0);
    gl::VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _stride, 0);
    gl::EnableVertexAttribArray(1);
    gl::VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _stride, (void *)(6 * sizeof(GLfloat)));
    gl::EnableVertexAttribArray(2);
    gl::VertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, _stride, (void *)(3 * sizeof(GLfloat)));
    gl::DrawArrays(GL_TRIANGLES, 0, _nVertex);

    // Unbind the VBO
    gl::BindBuffer(GL_ARRAY_BUFFER, 0);
}

void Triangle::SetPosition(float x, float y, float z)
{
    _position = glm::translate(glm::vec3(x, y, z));
}

bool Sphere::Init(pvr::Shell *shell, uint32_t* mvpLoc)
{
    const pvr::utils::VertexBindings_Name vertexBindings[] = {{"POSITION", "inVertex"}, {"NORMAL", "inNormal"}};
    _model = pvr::assets::loadModel(*shell, "sphere.pod");
    pvr::utils::appendSingleBuffersFromModel(*_model, _vbos, _ibos);
    _vertexConfiguration = createInputAssemblyFromMesh(_model->getMesh(0), vertexBindings, ARRAY_SIZE(vertexBindings));

    // Save the MVP matrix location for later use
    _mvp = mvpLoc[0];
    _mv = mvpLoc[1];
    _mvit = mvpLoc[2];
    _isSphere = mvpLoc[5];
    return true;
}

void Sphere::Render(glm::mat4 view, glm::mat4 projection)
{
    glm::mat4 model = _position * _rotation * glm::scale(glm::vec3(0.4f));

    glm::mat4 modelViewProj = projection * view * model;
    gl::UniformMatrix4fv(_mvp, 1, GL_FALSE, glm::value_ptr(modelViewProj));
    glm::mat4 modelView = view * model;
    gl::UniformMatrix4fv(_mv, 1, GL_FALSE, glm::value_ptr(modelView));
    glm::mat3 modelViewIT = glm::inverseTranspose(modelView);
    gl::UniformMatrix3fv(_mvit, 1, GL_FALSE, glm::value_ptr(modelViewIT));
    gl::Uniform1i(_isSphere, 1);
    for (uint32_t node = 0; node < _model->getNumMeshNodes(); ++node) {
        uint32_t meshId = _model->getMeshNode(node).getObjectId();
        gl::BindBuffer(GL_ARRAY_BUFFER, _vbos[meshId]);
        gl::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibos[meshId]);
        const pvr::assets::Mesh& mesh = _model->getMesh(meshId);
        for (uint32_t i = 0; i < _vertexConfiguration.attributes.size(); ++i)
        {
            auto& attrib = _vertexConfiguration.attributes[i];
            auto& binding = _vertexConfiguration.bindings[0];
            gl::EnableVertexAttribArray(attrib.index);
            gl::VertexAttribPointer(attrib.index, attrib.width, pvr::utils::convertToGles(attrib.format), dataTypeIsNormalised(attrib.format), binding.strideInBytes,
                reinterpret_cast<const void*>(static_cast<uintptr_t>(attrib.offsetInBytes)));
        }
        gl::DrawElements(GL_TRIANGLES, mesh.getNumFaces() * 3, pvr::utils::convertToGles(mesh.getFaces().getDataType()), nullptr);

        for (uint32_t i = 0; i < _vertexConfiguration.attributes.size(); ++i)
        {
            auto& attrib = _vertexConfiguration.attributes[i];
            gl::DisableVertexAttribArray(attrib.index);
        }
    }
}
