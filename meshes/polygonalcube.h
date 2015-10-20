#ifndef POLYGONALCUBE_H
#define POLYGONALCUBE_H

#include "mesh.h"

#include <QOpenGLTexture>

#include "material.h"

class PolygonalCube : public Mesh
{
public:
    PolygonalCube(int n, QOpenGLShaderProgram *program);
    ~PolygonalCube();

    virtual void render(QMatrix4x4& projection, QMatrix4x4& matrix, Light* light);

private:
    void initSide(VertexData* data, GLuint* ind, float x, float y, float z, float dx, float dy, float dz, int offset, int direction);
    void initTextures();
    void initShaders();
    void initGeometry(VertexData vertices[], GLuint indices[], int vertSize, int indSize, GLenum mode_);

private:
    int N;
    int vertices;
    int indices;

    float tt;
    float delta;

    VertexData* vertArray;
    GLuint* indArray;

    Material* material;

    QOpenGLTexture* texture;
    QOpenGLShader vShader;
    QOpenGLShader fShader;

    QOpenGLShaderProgram *program;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    int indicesSize;
    GLenum mode;
};

#endif // POLYGONALCUBE_H
