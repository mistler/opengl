#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"
#include "material.h"

class Sphere: public Mesh
{
public:
    Sphere(int numberOfPoints, QOpenGLShaderProgram *program);
    ~Sphere();

    virtual void render(QMatrix4x4& projection, QMatrix4x4& matrix, Light* light);

private:

    void initShaders();
    void initGeometry(VertexData vertices[], GLuint indices[], int vertSize, int indSize, GLenum mode_);

private:

    int vertices;
    int indices;


    float tt;
    float delta;

    VertexData* vertArray;
    GLuint* indArray;

    Material* material;

    QOpenGLShaderProgram *program;
    QOpenGLShader vShader;
    QOpenGLShader fShader;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    int indicesSize;
    GLenum mode;
};

#endif // SPHERE_H
