#ifndef MESH_H
#define MESH_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include <QVector2D>
#include <QVector3D>

#include "light.h"

struct VertexData{
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
};

class Mesh: protected QOpenGLFunctions{
public:

    virtual ~Mesh(){}
    virtual void render(QMatrix4x4& projection, QMatrix4x4& matrix, Light* light) = 0;

};

#endif // MESH_H
