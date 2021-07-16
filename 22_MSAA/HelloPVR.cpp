#include "PVRShell/PVRShell.h"
#include "PVRUtils/PVRUtilsGles.h"
#include "Triangle.h"

enum EUniform {
    eMVPMatrix,
    eMVMatrix,
    eMVITMatrix,
    eLightPosition,
    eLightColor,
    eNumUniforms
};
const char* sUniformNames[] = {
    "MVPMatrix", "MVMatrix", "MVITMatrix", "LightPosition", "LightColor"
};

GLuint uniLoc[eNumUniforms];

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
    GLuint _vbo;
    GLuint _fb;
    GLuint _tb;
    GLuint _width, _height;

    Triangle _triangle;
    Cube _cube;

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

/*!*********************************************************************************************************************
\return Return Result::Success if no error occurred
\brief  Code in initApplication() will be called by pvr::Shell once per run, before the rendering context is created.
    Used to initialize variables that are not dependent on it (e.g. external modules, loading meshes, etc.)
    If the rendering context is lost, initApplication() will not be called again.
***********************************************************************************************************************/
pvr::Result HelloPVR::initApplication()
{
    _triangle.SetPosition(-0.5, 0, 0);
    _cube.SetPosition(0.5, 0, 0);
    return pvr::Result::Success;
}

/*!*********************************************************************************************************************
\return Return Result::Success if no error occurred
\brief  Code in quitApplication() will be called by pvr::Shell once per run, just before exiting the program.
        If the rendering context is lost, QuitApplication() will not be called.
***********************************************************************************************************************/
pvr::Result HelloPVR::quitApplication()
{
    return pvr::Result::Success;
}

/*!*********************************************************************************************************************
\return Return Result::Success if no error occured
\brief  Code in initView() will be called by pvr::Shell upon initialization or after a change in the rendering context.
    Used to initialize variables that are dependant on the rendering context (e.g. textures, vertex buffers, etc.)
***********************************************************************************************************************/
pvr::Result HelloPVR::initView()
{
    // Initialize the PowerVR OpenGL bindings. Must be called before using any of the gl:: commands.
    _context = pvr::createEglContext();
    _context->init(getWindow(), getDisplay(), getDisplayAttributes());

    _width = getWidth();
    _height = getHeight();
    // Setup the text to be rendered
    _uiRenderer.init(_width, _height, isFullScreen(), (_context->getApiVersion() == pvr::Api::OpenGLES2) || (getBackBufferColorspace() == pvr::ColorSpace::sRGB));
    _uiRenderer.getDefaultTitle()->setText("OpenGLES MSAA");
    _uiRenderer.getDefaultTitle()->commitUpdates();

    static const char* attribs[] = {"inVertex", "inTexColor", "inNormal"};
    static const uint16_t attribIndices[] = {0, 1, 2};

    _program = pvr::utils::createShaderProgram(*this, "VertShader.vsh",
           "FragShader.fsh", attribs, attribIndices, 3, 0, 0);
    gl::GenFramebuffers(1, &_fb);
    gl::BindFramebuffer(GL_FRAMEBUFFER, _fb);
    gl::GenTextures(1, &_tb);
    gl::BindTexture(GL_TEXTURE_2D_MULTISAMPLE, _tb);
    gl::TexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, _width, _height, GL_TRUE);
    gl::BindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    gl::FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, _tb, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    GLuint rbo;
    gl::GenRenderbuffers(1, &rbo);
    gl::BindRenderbuffer(GL_RENDERBUFFER, rbo);
    gl::RenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, _width, _height);
    gl::BindRenderbuffer(GL_RENDERBUFFER, 0);
    gl::FramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    if (gl::CheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    gl::BindFramebuffer(GL_FRAMEBUFFER, 0);


    // Store the location of uniforms for later use
    for (int i = 0; i < eNumUniforms; ++i)
        uniLoc[i] = gl::GetUniformLocation(_program, sUniformNames[i]);

    if ((!_triangle.Init(this, uniLoc)) || (!_cube.Init(this, uniLoc)))
    {
        throw pvr::InvalidDataError(" ERROR: Triangle failed in Init()");
        return pvr::Result::UnknownError;
    }

    _camTheta = glm::radians(90.0f);
    _camRho = 2.0f;
    _projection = pvr::math::perspective(pvr::Api::OpenGLES2, 45, static_cast<float>(this->getWidth()) / static_cast<float>(this->getHeight()), 0.1, 100, 0);

    // Sets the clear color
    gl::ClearColor(0.0f, 0.4f, 0.7f, 1.0f);

    // Enable culling
    gl::Enable(GL_CULL_FACE);
    // Enable depth test
    gl::Enable(GL_DEPTH_TEST);
    return pvr::Result::Success;
}

/*!*********************************************************************************************************************
\return Return Result::Success if no error occurred
\brief  Code in releaseView() will be called by pvr::Shell when the application quits or before a change in the rendering context.
***********************************************************************************************************************/
pvr::Result HelloPVR::releaseView()
{
    // Release Vertex buffer object.
    if (_vbo)
        gl::DeleteBuffers(1, &_vbo);

    // Frees the OpenGL handles for the program and the 2 shaders
    gl::DeleteProgram(_program);
    return pvr::Result::Success;
}

/*!*********************************************************************************************************************
\return Return Result::Success if no error occurred
\brief  Main rendering loop function of the program. The shell will call this function every frame.
***********************************************************************************************************************/
pvr::Result HelloPVR::renderFrame()
{
    gl::BindFramebuffer(GL_FRAMEBUFFER, _fb);
    gl::Enable(GL_DEPTH_TEST);
    //  Clears the color buffer. glClear() can also be used to clear the depth or stencil buffer
    //  (GL_DEPTH_BUFFER_BIT or GL_STENCIL_BUFFER_BIT)
    gl::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gl::UseProgram(_program);

    if (pvr::Shell::isKeyPressed(pvr::Keys::Left))
        _camTheta += 0.01f;
    if (pvr::Shell::isKeyPressed(pvr::Keys::Right))
        _camTheta -= 0.01f;
    if (pvr::Shell::isKeyPressed(pvr::Keys::Up))
        _camRho += 0.1f;
    if (pvr::Shell::isKeyPressed(pvr::Keys::Down))
        _camRho -= 0.1f;

    _camPosition = glm::vec3(_camRho * cos(_camTheta), 0, _camRho * sin(_camTheta));
    glm::vec3 lightPosition = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::mat4 view = glm::lookAt(_camPosition, glm::vec3(0,0,0), glm::vec3(0, 1, 0));
    glm::vec3 viewLightPositon = glm::vec3((view * glm::vec4(lightPosition, 1)));
    gl::Uniform3fv(uniLoc[eLightPosition], 1, glm::value_ptr(viewLightPositon));
    gl::Uniform4fv(uniLoc[eLightColor], 1, glm::value_ptr(lightColor));

    _triangle.Update(0.01f);
    _cube.Update(-0.005f);

    _triangle.Render(view, _projection);
    _cube.Render(view, _projection);


    gl::BindFramebuffer(GL_READ_FRAMEBUFFER, _fb);
    gl::BindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    gl::BlitFramebuffer(0, 0, _width, _height, 0, 0, _width, _height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    gl::BindFramebuffer(GL_FRAMEBUFFER, 0);
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
    return std::unique_ptr<pvr::Shell>(new HelloPVR());
}
