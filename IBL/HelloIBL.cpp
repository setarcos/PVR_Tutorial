#include "PVRShell/PVRShell.h"
#include "PVRUtils/PVRUtilsGles.h"
#include "PVRCore/cameras/TPSCamera.h"

#include "Skybox.h"
#include "Helmet.h"

/*!*********************************************************************************************************************
 To use the shell, you have to inherit a class from PVRShell
 and implement the five virtual functions which describe how your application initializes, runs and releases the resources.
***********************************************************************************************************************/
class HelloIBL : public pvr::Shell
{
    pvr::EglContext _context;
    pvr::TPSOrbitCamera _camera;
    pvr::ui::UIRenderer _uiRenderer;
    Skybox* _skybox;
    Helmet* _helmet;
    glm::mat4 _projMtx;

public:
    // following function must be override
    virtual pvr::Result initApplication();
    virtual pvr::Result initView();
    virtual pvr::Result renderFrame();
    virtual pvr::Result releaseView();
    virtual pvr::Result quitApplication();
};

pvr::Result HelloIBL::initApplication()
{
    _skybox = new Skybox();
    _helmet = new Helmet();
    return pvr::Result::Success;
}

pvr::Result HelloIBL::quitApplication()
{
    delete _skybox;
    delete _helmet;
    return pvr::Result::Success;
}

pvr::Result HelloIBL::initView()
{
    // Initialize the PowerVR OpenGL bindings. Must be called before using any of the gl:: commands.
    _context = pvr::createEglContext();
    _context->init(getWindow(), getDisplay(), getDisplayAttributes());

    // Setup the text to be rendered
    _uiRenderer.init(getWidth(), getHeight(), isFullScreen(), (_context->getApiVersion() == pvr::Api::OpenGLES2) || (getBackBufferColorspace() == pvr::ColorSpace::sRGB));
    _uiRenderer.getDefaultTitle()->setText("Image Based Lighting");
    _uiRenderer.getDefaultTitle()->commitUpdates();

    // Sets the clear color
    gl::ClearColor(0.0f, 0.4f, 0.7f, 1.0f);
    _camera.setDistanceFromTarget(50.f);
    _camera.setInclination(10.f);
    _projMtx = pvr::math::perspectiveFov(pvr::Api::OpenGLES31, glm::radians(65.0), static_cast<float>(this->getWidth()), static_cast<float>(this->getHeight()), 0.1f, 2000.f);

    _skybox->Init(this);
    _helmet->Init(this);

    // Enable culling
    gl::Enable(GL_CULL_FACE);
    return pvr::Result::Success;
}

pvr::Result HelloIBL::releaseView()
{
    return pvr::Result::Success;
}

/*!*********************************************************************************************************************
\return Return Result::Success if no error occurred
\brief  Main rendering loop function of the program. The shell will call this function every frame.
***********************************************************************************************************************/
pvr::Result HelloIBL::renderFrame()
{
    //  Clears the color buffer. glClear() can also be used to clear the depth or stencil buffer
    //  (GL_DEPTH_BUFFER_BIT or GL_STENCIL_BUFFER_BIT)
    gl::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _camera.addAzimuth(0.3);
    const glm::mat4 viewProj = _projMtx * _camera.getViewMatrix();

    _skybox->Render(viewProj, _camera.getCameraPosition());
    _helmet->Render(viewProj, _camera.getCameraPosition());
    // Display some text
    _uiRenderer.beginRendering();
    _uiRenderer.getDefaultTitle()->render();
    _uiRenderer.endRendering();

    _context->swapBuffers();
    return pvr::Result::Success;
}

/// <summary>This function must be implemented by the user of the shell. The user should return its pvr::Shell object defining the behaviour of the application.</summary>
/// <returns>Return a unique ptr to the demo supplied by the user.</returns>
std::unique_ptr<pvr::Shell> pvr::newDemo()
{
    return std::unique_ptr<pvr::Shell>(new HelloIBL());
}
