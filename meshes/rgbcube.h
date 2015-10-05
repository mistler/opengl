#ifndef RGBCUBE_H
#define RGBCUBE_H

#include "mesh.h"

class RgbCube: public Mesh{
public:
    RgbCube();
    ~RgbCube();

    void render(QOpenGLShaderProgram *program);

private:
    GLfloat* cubeVertexArray;
    GLfloat* cubeColorArray;
    GLubyte* cubeIndexArray;
};

#endif // RGBCUBE_H
