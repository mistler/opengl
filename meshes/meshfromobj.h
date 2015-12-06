#ifndef MESHFROMOBJ_H
#define MESHFROMOBJ_H

#include "mesh.h"

#include <string>

#include "material.h"

class MeshFromObj : public Mesh
{
public:
    MeshFromObj(QOpenGLShaderProgram *program, std::string filename);
    ~MeshFromObj();

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

#endif // MESHFROMOBJ_H
