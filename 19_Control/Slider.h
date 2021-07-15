#pragma once
#include "PVRShell/PVRShell.h"

class Slider {
private:
    GLuint _program;
    GLuint _xpos, _ypos;
    GLuint _winW, _winH;
    GLuint _pLoc, _vLoc;
    GLuint _value;
public:
    Slider(GLuint px, GLuint py, GLuint wx, GLuint wy);
    void Init(pvr::Shell* assetProvider);
    void Render(void);
    void SetValue(GLuint v);
    void Click(pvr::PointerLocation loc);
    GLuint GetValue() {return _value; }
    ~Slider(void);
};
