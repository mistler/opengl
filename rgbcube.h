#ifndef RGBCUBE_H
#define RGBCUBE_H

#include <QtGui>
#include <QGLWidget>
#include <iostream>

#include "mesh.h"

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
