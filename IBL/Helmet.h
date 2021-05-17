#pragma once
#include "PVRShell/PVRShell.h"

class Helmet {
private:
    pvr::assets::ModelHandle _model;
    pvr::utils::VertexConfiguration _vertexConfiguration;
    std::vector<GLuint> _vbos;
    std::vector<GLuint> _ibos;
    GLuint _program;
    GLuint _vp;
    GLuint _cpos;
    std::vector<GLuint> _textures;

public:
    void Init(pvr::Shell* assetProvider);
    void Render(const glm::mat4& viewProj, const glm::vec3& eyePos);
    void RenderMesh(uint32_t meshNodeId);
    ~Helmet(void);
};
