#pragma once
#include "PVRShell/PVRShell.h"
#include "PVRUtils/PVRUtilsGles.h"

class Triangle
{
private:
    // VBO handle
    uint32_t _vbo;

    // MVP Matrix location
    uint32_t _mvp;

    // Matrix for the Model position
    glm::mat4 _position;

    // Matrix for the Model rotation
    glm::mat4 _rotation;

public:
    Triangle(void);
    ~Triangle(void);

    void Update(float angle);
    bool Init(pvr::Shell *shell, uint32_t mvpLoc);
    void Render(glm::mat4 projection);
    void SetPosition(float x, float y, float z);
};

