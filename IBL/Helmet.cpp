#include "PVRUtils/PVRUtilsGles.h"
#include "Helmet.h"

void Helmet::Init(pvr::Shell* assetProvider)
{
    _model = pvr::assets::loadModel(*assetProvider, "damagedHelmet.gltf");
    pvr::utils::appendSingleBuffersFromModel(*_model, _vbos, _ibos);

    // Load Textures
    for (uint32_t i = 0; i < _model->getNumTextures(); ++i)
    {
        std::unique_ptr<pvr::Stream> stream = assetProvider->getAssetStream(_model->getTexture(i).getName());
        pvr::Texture tex = pvr::textureLoad(*stream, pvr::TextureFileFormat::PVR);
        _textures.push_back(pvr::utils::textureUpload(tex, false, true).image);
    }

    // Create program
    _program = pvr::utils::createShaderProgram(*assetProvider, "VertShader.vsh", 
            "FragShader.fsh", nullptr, nullptr, 0, 0, 0);
    const pvr::assets::Mesh& mesh = _model->getMesh(0);
    const pvr::utils::VertexBindings_Name vertexBindings[] = { { "POSITION", "inVertex" }, { "NORMAL", "inNormal" }, { "UV0", "inTexCoord" }, { "TANGENT", "inTangent" } };
    _vertexConfiguration = createInputAssemblyFromMesh(mesh, vertexBindings, ARRAY_SIZE(vertexBindings));
    _vp = gl::GetUniformLocation(_program, "VPMatrix");
    //_cpos = gl::GetUniformLocation(_program, "camPos");
}

void Helmet::RenderMesh(uint32_t meshNodeId)
{
    const pvr::assets::Model::Node* pNode = &_model->getMeshNode(meshNodeId);
    const uint32_t meshId = pNode->getObjectId();
    // Gets pMesh referenced by the pNode
    const pvr::assets::Mesh* pMesh = &_model->getMesh(meshId);

    // bind the vertex and index buffer
    gl::BindBuffer(GL_ARRAY_BUFFER, _vbos[meshId]);
    gl::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibos[meshId]);

    // set the vertex attribute pointers
    for (size_t i = 0; i < _vertexConfiguration.attributes.size(); ++i)
    {
        auto& attrib = _vertexConfiguration.attributes[i];
        auto& binding = _vertexConfiguration.bindings[0];

        gl::EnableVertexAttribArray(attrib.index);
        gl::VertexAttribPointer(attrib.index, attrib.width, pvr::utils::convertToGles(attrib.format), dataTypeIsNormalised(attrib.format), binding.strideInBytes,
            reinterpret_cast<const void*>(static_cast<uintptr_t>(attrib.offsetInBytes)));
    }
    gl::DrawElements(GL_TRIANGLES, pMesh->getNumFaces() * 3, pvr::utils::convertToGles(pMesh->getFaces().getDataType()), nullptr);

    for (uint32_t i = 0; i < _vertexConfiguration.attributes.size(); ++i)
    {
        auto& attrib = _vertexConfiguration.attributes[i];
        gl::DisableVertexAttribArray(attrib.index);
    }
}

void Helmet::Render(const glm::mat4& viewProj, const glm::vec3& eyePos)
{
    // bind the albedo texture
    gl::ActiveTexture(GL_TEXTURE0);
    gl::BindTexture(GL_TEXTURE_2D, _textures[0]);

    // bind the metallic roughness texture
    gl::ActiveTexture(GL_TEXTURE1);
    gl::BindTexture(GL_TEXTURE_2D, _textures[1]);

    // bind the normal texture
    gl::ActiveTexture(GL_TEXTURE2);
    gl::BindTexture(GL_TEXTURE_2D, _textures[2]);

    // bind the emissive map
    gl::ActiveTexture(GL_TEXTURE3);
    gl::BindTexture(GL_TEXTURE_2D, _textures[3]);

    gl::UseProgram(_program);
    gl::UniformMatrix4fv(_vp, 1, GL_FALSE, glm::value_ptr(viewProj));
    gl::Uniform3fv(_cpos, 1, glm::value_ptr(eyePos));
    for (uint32_t i = 0; i < _model->getNumMeshNodes(); ++i) {
        RenderMesh(i);
    }
}

Helmet::~Helmet(void)
{
    if (_program) {
        gl::DeleteProgram(_program);
    }
    if (_vbos.size()) {
        gl::DeleteBuffers(static_cast<GLsizei>(_vbos.size()), _vbos.data());
        _vbos.clear();
    }
    if (_ibos.size()) {
        gl::DeleteBuffers(static_cast<GLsizei>(_ibos.size()), _ibos.data());
        _ibos.clear();
    }
    gl::DeleteTextures(static_cast<GLsizei>(_textures.size()), _textures.data());
}
