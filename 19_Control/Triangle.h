#pragma once
#include "PVRShell/PVRShell.h"
#include "PVRUtils/PVRUtilsGles.h"

class Triangle
{
protected:
    // VBO handle
    uint32_t _vbo;

    // Texture handle
    uint32_t _texture;

    // MVP Matrix location
    uint32_t _mvp;
    uint32_t _mv;
    uint32_t _mvit;

    uint32_t _nVertex;

    // Matrix for the Model position
    glm::mat4 _position;

    // Matrix for the Model rotation
    glm::mat4 _rotation;

public:
    Triangle(void);
    ~Triangle(void);

    void Update(float angle);
    bool Init(pvr::Shell *shell, uint32_t* mvpLoc);
    void Render(glm::mat4 view, glm::mat4 projection);
    void SetPosition(float x, float y, float z);
};

class Sphere: public Triangle
{
public:
    bool Init(pvr::Shell *shell, uint32_t* mvpLoc);
    void Render(glm::mat4 view, glm::mat4 projection);
private:
    uint32_t _isSphere;
    pvr::assets::ModelHandle _model;
    std::vector<GLuint> _vbos;
    std::vector<GLuint> _ibos;
    pvr::utils::VertexConfiguration _vertexConfiguration;
};
