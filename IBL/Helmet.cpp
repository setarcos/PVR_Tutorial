#include "PVRUtils/PVRUtilsGles.h"
#include "Helmet.h"

const std::string otherTextures[] = {"irradiance.pvr", "prefiltered.pvr", "brdfLUT.pvr"};

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

    for (int i = 0; i < 3; ++i)
        _textures.push_back(pvr::utils::textureUpload(*assetProvider, otherTextures[i]));
    _brdf = _textures.size() - 1;
    pvr::Texture tdata = pvr::utils::getTextureData(*assetProvider, otherTextures[1].data());
    GLuint numMips = tdata.getNumMipMapLevels();

    // Create program
    _program = pvr::utils::createShaderProgram(*assetProvider, "VertShader.vsh", 
            "FragShader.fsh", nullptr, nullptr, 0, 0, 0);
    const pvr::assets::Mesh& mesh = _model->getMesh(0);
    const pvr::utils::VertexBindings_Name vertexBindings[] = { { "POSITION", "inVertex" }, { "NORMAL", "inNormal" }, { "UV0", "inTexCoord" }, { "TANGENT", "inTangent" } };
    _vertexConfiguration = createInputAssemblyFromMesh(mesh, vertexBindings, ARRAY_SIZE(vertexBindings));
    _vp = gl::GetUniformLocation(_program, "VPMatrix");
    _cpos = gl::GetUniformLocation(_program, "camPos");
    GLuint mips = gl::GetUniformLocation(_program, "numPrefilteredMipLevels");
    gl::UseProgram(_program);
    gl::Uniform1ui(mips, numMips);
}

void Helmet::SetEnvironmentMap(GLuint mapId)
{
    _textures.push_back(mapId);
    gl::BindTexture(GL_TEXTURE_CUBE_MAP, mapId);
    gl::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gl::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    gl::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_LOD, 2.f); // 256
}

void Helmet::SetSamplers(void)
{
    gl::GenSamplers(1, &_sampler);
    gl::SamplerParameteri(_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gl::SamplerParameteri(_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl::SamplerParameteri(_sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl::SamplerParameteri(_sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (int i = 0; i < _brdf; ++i)
        gl::BindSampler(i, _sampler);
    gl::BindSampler(9, _sampler);
    gl::BindTexture(GL_TEXTURE_2D, _brdf);
    gl::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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

    // bind the diffuse irradiance map
    gl::ActiveTexture(GL_TEXTURE5);
    gl::BindTexture(GL_TEXTURE_CUBE_MAP, _textures[4]);

    // bind the prefiltered map
    gl::ActiveTexture(GL_TEXTURE6);
    gl::BindTexture(GL_TEXTURE_CUBE_MAP, _textures[5]);

    // bind the brdf lut texture
    gl::ActiveTexture(GL_TEXTURE7);
    gl::BindTexture(GL_TEXTURE_2D, _textures[6]);

    // bind the environment map
    gl::ActiveTexture(GL_TEXTURE8);
    gl::BindTexture(GL_TEXTURE_CUBE_MAP, _textures[7]);

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
    gl::DeleteSamplers(1, &_sampler);
    // the last textures is from skybox
    gl::DeleteTextures(static_cast<GLsizei>(_textures.size() - 1), _textures.data());
}
