#pragma once
#include "PVRShell/PVRShell.h"
#include "PVRUtils/PVRUtilsGles.h"

class Triangle
{
private:
    // VBO handle
    uint32_t _vbo;

    // Texture handle
    uint32_t _texture;

    // MVP Matrix location
    uint32_t _mvp;

    // Matrix for the Model position
    glm::mat4 _position;

public:
    Triangle(void);
    ~Triangle(void);

    bool Init(pvr::Shell *shell, uint32_t mvpLoc);
    void Render(glm::mat4 projection);
    void SetPosition(float x, float y, float z);
};

