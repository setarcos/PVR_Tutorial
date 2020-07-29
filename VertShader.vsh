attribute highp vec4    myVertex;
attribute mediump vec4  myColor;
uniform mediump mat4    myPMVMatrix;
varying mediump vec4    fColor;
void main(void)
{
    gl_Position = myPMVMatrix * myVertex;
    fColor = myColor;
}
