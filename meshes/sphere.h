#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"

#include <QOpenGLTexture>

class Sphere: public Mesh
{
public:
    Sphere(int numberOfPoints, QOpenGLShaderProgram *program);
    ~Sphere();

    virtual void render();

private:

    void initShaders();
    void initTextures();

private:

    int vertices;
    int indices;


    float tt;
    float delta;

    VertexData* vertArray;
    GLuint* indArray;

    QOpenGLTexture* texture;
};

#endif // SPHERE_H
