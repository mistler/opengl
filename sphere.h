#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"

#include <QtGui>
#include <QGLWidget>

class Sphere: public Mesh
{
public:
    Sphere(int numberOfPoints);
    ~Sphere();

    void render();

private:

    int n, t;
    int vertices;
    int indexes;

    GLfloat* vertexArray;
    GLfloat* colorArray;
    GLuint* indexArray;
};

#endif // SPHERE_H
