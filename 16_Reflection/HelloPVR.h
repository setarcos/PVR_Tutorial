#pragma once

enum EUniform {
    eMVPMatrix,
    eMVMatrix,
    eMVITMatrix,
    eMMatrix,
    eMITMatrix,
    eLightPosition,
    eCamPosition,
    eLightColor,
    eTexture,
    eSkyBox,
    eNumUniforms
};

/*!*********************************************************************************************************************
 To use the shell, you have to inherit a class from PVRShell
 and implement the five virtual functions which describe how your application initializes, runs and releases the resources.
***********************************************************************************************************************/
class HelloPVR : public pvr::Shell
{
    pvr::EglContext _context;
    // UIRenderer used to display text
    pvr::ui::UIRenderer _uiRenderer;
    GLuint _program;

    Triangle _triangle;
    Cube _cube;
    CubeMap _map;

    glm::vec3 _camPosition;
    glm::mat4 _projection;
    float _camTheta;
    float _camRho;

public:
    // following function must be override
    virtual pvr::Result initApplication();
    virtual pvr::Result initView();
    virtual pvr::Result renderFrame();
    virtual pvr::Result releaseView();
    virtual pvr::Result quitApplication();
};
