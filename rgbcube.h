#ifndef RGBCUBE_H
#define RGBCUBE_H

#include "mesh.h"

#include <QtGui>
#include <QGLWidget>

class RgbCube: public Mesh{
public:
    RgbCube();
    ~RgbCube();

    void render();

private:
    GLfloat* cubeVertexArray;
    GLfloat* cubeColorArray;
    GLubyte* cubeIndexArray;
};

#endif // RGBCUBE_H
