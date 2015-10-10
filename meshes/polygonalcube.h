#ifndef POLYGONALCUBE_H
#define POLYGONALCUBE_H

#include "mesh.h"

#include <QOpenGLTexture>

class PolygonalCube : public Mesh
{
public:
    PolygonalCube(int n, QOpenGLShaderProgram *program);
    ~PolygonalCube();

    virtual void render();

private:
    void initSide(VertexData* data, GLuint* ind, float x, float y, float z, float dx, float dy, float dz, int offset);
    void initTextures();
    void initShaders();

private:
    int N;
    int vertices;
    int indices;

    float tt;
    float delta;

    VertexData* vertArray;
    GLuint* indArray;

    QOpenGLTexture* texture;
};

#endif // POLYGONALCUBE_H
