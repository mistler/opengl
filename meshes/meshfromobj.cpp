#include "meshfromobj.h"

#include <cmath>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>

#include "materials/defaultmaterial.h"


MeshFromObj::MeshFromObj(QOpenGLShaderProgram* program, std::string filename): indexBuf(QOpenGLBuffer::IndexBuffer),
                                                        vShader(QOpenGLShader::Vertex),
                                                        fShader(QOpenGLShader::Fragment),
                                                        material(new DefaultMaterial(program)){

    initializeOpenGLFunctions();
    this->program = program;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    initShaders();



    std::ifstream fin(filename.c_str());
    std::setlocale(LC_NUMERIC, "C");
    std::vector<float> vectorVert;
    std::vector<int> vectorInd;
    std::string line;

    while(!fin.eof()){
        std::getline(fin, line);
        if(line[0] == 'v' && line[1] == ' '){
            line[0] = ' ';
            double tmp[3];
            sscanf(line.c_str(), "%lf%lf%lf", tmp + 0, tmp + 1, tmp + 2);
            vectorVert.push_back(tmp[0]);
            vectorVert.push_back(tmp[1]);
            vectorVert.push_back(tmp[2]);
        }else if(line[0] == 'f' && line[1] == ' '){
            line[0] = ' ';
            int tmp[3];
            sscanf(line.c_str(), "%i/%i/%i %i/%i/%i %i/%i/%i", tmp + 0, tmp + 0, tmp + 0, tmp + 1, tmp + 1, tmp + 1, tmp + 2, tmp + 2, tmp + 2);
            tmp[0] -= 1;
            tmp[1] -= 1;
            tmp[2] -= 1;
            vectorInd.push_back(tmp[0]);
            vectorInd.push_back(tmp[1]);
            vectorInd.push_back(tmp[2]);
        }
    }

    fin.close();

    tt = 0.0f;
    delta = 0.01f;

    vertices = vectorVert.size() / 3;
    indices = vectorInd.size();
    vertArray = new VertexData[vertices];
    indArray = new GLuint[indices];

    for(int i = 0; i < vertices; i++){
        QVector3D v(vectorVert[i*3 + 0], vectorVert[i*3 + 1], vectorVert[i*3 + 2]);
        QVector2D t(0.0f, 0.0f);
        QVector3D n = v;
        vertArray[i] = {v, t, n};
    }

    for(int i = 0; i < indices; i++){
        indArray[i] = vectorInd[i];
    }

    srand(time(NULL));

    initGeometry(vertArray, indArray, vertices, indices, GL_TRIANGLES);
}

MeshFromObj::~MeshFromObj(){
    arrayBuf.destroy();
    indexBuf.destroy();
    delete[] vertArray;
    delete[] indArray;
    delete material;
}

void MeshFromObj::render(QMatrix4x4& projection, QMatrix4x4& matrix, Light* light){

    program->addShader(&vShader);
    program->addShader(&fShader);
    program->link();
    program->bind();

    program->setUniformValue("mvp_matrix", projection * matrix);
    program->setUniformValue("mv_matrix", matrix);
    program->setUniformValue("normal_matrix", matrix.transposed().inverted());

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

    offset += sizeof(QVector2D);

    int normalLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));


    light->load(program);
    material->load(program);


    // Draw cube geometry using indices from VBO 1
    glDrawElements(mode, indicesSize, GL_UNSIGNED_INT, 0);

    program->release();
}

void MeshFromObj::initShaders(){

    vShader.compileSourceFile(":/vsphere.glsl");
    fShader.compileSourceFile(":/fsphere.glsl");


}

void MeshFromObj::initGeometry(VertexData vertices[], GLuint indices[], int vertSize, int indSize, GLenum mode_){
    indicesSize = indSize;
    mode = mode_;

    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertSize * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, indSize * sizeof(GLuint));
}
