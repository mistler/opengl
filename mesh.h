#ifndef MESH_H
#define MESH_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include <QVector2D>
#include <QVector3D>

struct VertexData{
    QVector3D position;
    QVector2D texCoord;
};

class Mesh: protected QOpenGLFunctions{
public:
    Mesh(): indexBuf(QOpenGLBuffer::IndexBuffer){
        initializeOpenGLFunctions();

        // Generate 2 VBOs
        arrayBuf.create();
        indexBuf.create();
    }
    virtual ~Mesh(){
        arrayBuf.destroy();
        indexBuf.destroy();
    }

    virtual void render(QOpenGLShaderProgram *program){
        // Tell OpenGL which VBOs to use
        arrayBuf.bind();
        indexBuf.bind();

        // Offset for position
        quintptr offset = 0;

        // Tell OpenGL programmable pipeline how to locate vertex position data
        int vertexLocation = program->attributeLocation("a_position");
        program->enableAttributeArray(vertexLocation);
        program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

        // Offset for texture coordinate
        offset += sizeof(QVector3D);

        // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
        int texcoordLocation = program->attributeLocation("a_texcoord");
        program->enableAttributeArray(texcoordLocation);
        program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

        // Draw cube geometry using indices from VBO 1
        glDrawElements(mode, indicesSize, GL_UNSIGNED_INT, 0);
    }


protected:
    virtual void initGeometry(VertexData vertices[], GLuint indices[], int vertSize, int indSize, GLenum mode_){
        indicesSize = indSize;
        mode = mode_;

        arrayBuf.bind();
        arrayBuf.allocate(vertices, vertSize * sizeof(VertexData));

        // Transfer index data to VBO 1
        indexBuf.bind();
        indexBuf.allocate(indices, indSize * sizeof(GLuint));
    }

protected:
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    int indicesSize;
    GLenum mode;
};

#endif // MESH_H
