#include "PVRUtils/PVRUtilsGles.h"
#include "Slider.h"

Slider::Slider(GLuint px, GLuint py, GLuint wx, GLuint wy): _xpos(px),
    _ypos(py), _winW(wx), _winH(wy), _value(0)
{}

void Slider::Init(pvr::Shell* assetProvider)
{
    _program = pvr::utils::createShaderProgram(*assetProvider,
            "Slider.vsh", "Slider.fsh", nullptr, nullptr, 0, 0, 0);
    _pLoc = gl::GetUniformLocation(_program, "Pos");
    _vLoc = gl::GetUniformLocation(_program, "value");
    glm::vec2 pos;
    pos[0] = float(_xpos) / _winW * 2 - 1;
    pos[1] = float(_ypos) / _winH * 2 - 1;
    gl::UseProgram(_program);
    gl::Uniform2fv(_pLoc, 1, glm::value_ptr(pos));
}

Slider::~Slider(void)
{
    if (_program) gl::DeleteProgram(_program);
}

void Slider::Render(void)
{
    gl::UseProgram(_program);
    gl::Disable(GL_DEPTH_TEST);
    gl::DrawArrays(GL_TRIANGLE_FAN, 0, 4);
    gl::Enable(GL_DEPTH_TEST);
}

void Slider::SetValue(GLuint v)
{
    _value = v;
    if (_program) {
        gl::UseProgram(_program);
        float val = _xpos + _winW / 2 * 0.3 * v / 100;
        gl::Uniform1f(_vLoc, val);
    }
}

void Slider::Click(pvr::PointerLocation loc)
{
    if ((loc.x < _xpos) || (loc.x > _xpos + _winW / 2 * 0.3)) return;
    if ((loc.y > _ypos) || (loc.x < _ypos - _winH / 2 * 0.1)) return;
    SetValue(round((loc.x - _xpos) * 200 / (_winW  * 0.3)));
}
