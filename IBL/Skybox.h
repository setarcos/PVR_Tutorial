#pragma once
#include "PVRShell/PVRShell.h"

class Skybox
{
private:
    GLuint _program;
    GLuint _skyBoxMap;
    GLuint _ivp;
    GLuint _epos;
public:
    Skybox(void);
    ~Skybox(void);
    void Init(pvr::Shell* shell);
    void CleanUp(void);
    void Render(const glm::mat4& viewProj, const glm::vec3& eyePos);
};
