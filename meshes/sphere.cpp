#include "meshes/sphere.h"

#include <cmath>
#include <iostream>
#include <time.h>
#include <stdlib.h>

Sphere::Sphere(int numberOfPoints, QOpenGLShaderProgram *program):
    vShader(QOpenGLShader::Vertex),
    fShader(QOpenGLShader::Fragment){

    initializeOpenGLFunctions();
    this->program = program;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    initShaders();
    initTextures();

    tt = 0.0f;
    delta = 0.01f;

    int t = numberOfPoints;
    vertices = 2 * (t + 1) * t;
    indices = 4 * t * t + 2 * t;
    vertArray = new VertexData[vertices];
    indArray = new GLuint[indices];
    double d = (double)M_PI / t;
    int k = 0;
    double i = 0.;
    double j = 0.;

    srand(time(NULL));

    for(int iter = 0; iter <= t; iter++){
        double sini = sin(i);
        double cosi = cos(i);
        for(int jter = 0; jter < 2 * t; jter++){
            vertArray[k++] = {QVector3D(sini * cos(j), cosi, sin(j) * sini), QVector2D(0.0f, 0.0f)};
            j += d;
        }
        i += d;
    }
    k = 0;
    for(int i = 0; i < t; i++){
        for(int j = 0; j < 2 * t; j++){
            indArray[k++] = j + i * 2 * t;
            indArray[k++] = j + (i + 1) * 2 * t;
        }
        indArray[k++] = i * 2 * t;
        indArray[k++] = (i + 1) * 2 * t;
    }


    initGeometry(vertArray, indArray, vertices, indices, GL_TRIANGLE_STRIP);
}

void Sphere::initTextures(){

    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Sphere::initShaders(){

    vShader.compileSourceFile(":/vsphere.glsl");
    fShader.compileSourceFile(":/fsphere.glsl");

}

void Sphere::render(QMatrix4x4& projection, QMatrix4x4& matrix){


    program->addShader(&vShader);
    program->addShader(&fShader);
    /*
    // Compile vertex shader
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");

    // Compile fragment shader
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    */
    // Link shader pipeline
    program->link();


    // Bind shader pipeline for use
    program->bind();

    program->setUniformValue("mvp_matrix", projection * matrix);

    texture->bind();

    // Use texture unit 0 which contains cube.png
    program->setUniformValue("texture", 0);


    tt += delta;
    if(tt > 1.0f){
        delta = -delta;
        tt += delta;
    }
    if(tt < 0.0f){
        delta = -delta;
        tt += delta;
    }

    int timeLocation = program->attributeLocation("a_time");
    program->setAttributeValue(timeLocation, tt);

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

Sphere::~Sphere(){
    arrayBuf.destroy();
    indexBuf.destroy();
    delete texture;
    delete[] vertArray;
    delete[] indArray;
}

void Sphere::initGeometry(VertexData vertices[], GLuint indices[], int vertSize, int indSize, GLenum mode_){
    indicesSize = indSize;
    mode = mode_;

    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertSize * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, indSize * sizeof(GLuint));
}

