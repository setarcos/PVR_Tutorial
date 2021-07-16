#include "PVRUtils/PVRUtilsGles.h"

#include "Skybox.h"

Skybox::Skybox(void): _program(0), _skyBoxMap(0), _ivp(0), _epos(0)
{
}

void Skybox::Init(pvr::Shell *shell)
{
    _program = pvr::utils::createShaderProgram(*shell, "SkyVertShader.vsh",
           "SkyFragShader.fsh", nullptr, nullptr, 0, 0, 0);
    _skyBoxMap = pvr::utils::textureUpload(*shell, "Skybox.pvr");
    gl::BindTexture(GL_TEXTURE_CUBE_MAP, _skyBoxMap);
    gl::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gl::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    _ivp = gl::GetUniformLocation(_program, "InvVPMatrix");
    _epos = gl::GetUniformLocation(_program, "EyePos");
}

void Skybox::CleanUp(void)
{
    if (_program) {
        gl::DeleteProgram(_program);
        _program = 0;
    }
}

void Skybox::Render(const glm::mat4& viewProj, const glm::vec3& eyePos)
{
    gl::ActiveTexture(GL_TEXTURE9);
    gl::BindTexture(GL_TEXTURE_CUBE_MAP, _skyBoxMap);

    gl::Disable(GL_DEPTH_TEST);
    gl::UseProgram(_program);
    gl::UniformMatrix4fv(_ivp, 1, GL_FALSE, glm::value_ptr(glm::inverse(viewProj)));
    gl::Uniform3fv(_epos, 1, glm::value_ptr(eyePos));
    gl::DrawArrays(GL_TRIANGLE_FAN, 0, 4);
    gl::Enable(GL_DEPTH_TEST);
}

Skybox::~Skybox()
{
    CleanUp();
}
