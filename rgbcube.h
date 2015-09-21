#ifndef RGBCUBE_H
#define RGBCUBE_H

#include <QtGui>
#include <QGLWidget>
#include <iostream>

class RgbCube
{
public:
    RgbCube();
    ~RgbCube();

    void show();

private:
    GLfloat* cubeVertexArray;
    GLfloat* cubeColorArray;
    GLubyte* cubeIndexArray;
};

#endif // RGBCUBE_H
