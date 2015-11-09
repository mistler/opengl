#include "meshes/polygonalcube.h"
#include "materials/defaultmaterial.h"

PolygonalCube::PolygonalCube(int n, QOpenGLShaderProgram* program): indexBuf(QOpenGLBuffer::IndexBuffer),
                                                                    vShader(QOpenGLShader::Vertex),
                                                                    fShader(QOpenGLShader::Fragment),
                                                                    material(new DefaultMaterial(program)){

    initializeOpenGLFunctions();
    this->program = program;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    initShaders();

    tt = 0.0f;
    delta = 0.01f;

    N = n;

    vertices = (n + 1) * (n + 1) * 6;
    indices = (n) * (2 * (n + 1) + 2) * 6;

    vertArray = new VertexData[vertices];
    indArray = new GLuint[indices];


    initSide(vertArray + (N+1) * (N+1) * 0, indArray + (N)*((N+1) * 2 + 2) * 0,  1.0f, -1.0f, -1.0f,
             -1.0f / n * 2,  1.0f / n * 2,  0.0f / n * 2, (N+1) * (N+1) * 0, -1);
    initSide(vertArray + (N+1) * (N+1) * 1, indArray + (N)*((N+1) * 2 + 2) * 1, -1.0f,  1.0f, -1.0f,
              1.0f / n * 2,  0.0f / n * 2,  1.0f / n * 2, (N+1) * (N+1) * 1, 1);
    initSide(vertArray + (N+1) * (N+1) * 2, indArray + (N)*((N+1) * 2 + 2) * 2,  1.0f,  1.0f,  1.0f,
             -1.0f / n * 2, -1.0f / n * 2,  0.0f / n * 2, (N+1) * (N+1) * 2, 1);
    initSide(vertArray + (N+1) * (N+1) * 3, indArray + (N)*((N+1) * 2 + 2) * 3,  1.0f,  1.0f, -1.0f,
              0.0f / n * 2, -1.0f / n * 2,  1.0f / n * 2, (N+1) * (N+1) * 3, 1);
    initSide(vertArray + (N+1) * (N+1) * 4, indArray + (N)*((N+1) * 2 + 2) * 4, -1.0f, -1.0f,  1.0f,
              1.0f / n * 2,  0.0f / n * 2, -1.0f / n * 2, (N+1) * (N+1) * 4, -1);
    initSide(vertArray + (N+1) * (N+1) * 5, indArray + (N)*((N+1) * 2 + 2) * 5, -1.0f,  1.0f,  1.0f,
              0.0f / n * 2, -1.0f / n * 2, -1.0f / n * 2, (N+1) * (N+1) * 5, -1);

    initGeometry(vertArray, indArray, vertices, indices, GL_TRIANGLE_STRIP);

}

PolygonalCube::~PolygonalCube(){
    arrayBuf.destroy();
    indexBuf.destroy();
    delete[] vertArray;
    delete[] indArray;

    delete material;
}

void PolygonalCube::initSide(VertexData* data, GLuint* ind, float x, float y, float z, float dx, float dy, float dz, int offset, int direction){
    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= N; j++){
            if(dx == 0){
                data[i * (N+1) + j] = {QVector3D(x, y + dy * i, z + dz * j), QVector2D(0.0f, 0.0f), QVector3D(1.0f * direction, 0.0f, 0.0f)};
            }
            if(dy == 0){
                data[i * (N+1) + j] = {QVector3D(x + dx * i, y, z + dz * j), QVector2D(0.0f, 0.0f), QVector3D(0.0f, 1.0f * direction, 0.0f)};
            }
            if(dz == 0){
                data[i * (N+1) + j] = {QVector3D(x + dx * j, y + dy * i, z), QVector2D(0.0f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f * direction)};
            }
        }
    }
    int k = 0;
    for(int i = 0; i < N; i++){
        ind[k++] = i * (N+1) + offset;
        for(int j = 0; j <= N; j++){
            ind[k++] = j + i * (N+1) + offset;
            ind[k++] = j + (i + 1) * (N+1) + offset;
        }
        ind[k++] = (i + 1) * (N+1) + N + offset;
    }
}

void PolygonalCube::render(QMatrix4x4& projection, QMatrix4x4& matrix, Light* light){


    program->addShader(&vShader);
    program->addShader(&fShader);
    program->link();
    program->bind();

    program->setUniformValue("mvp_matrix", projection * matrix);
    program->setUniformValue("mv_matrix", matrix);
    program->setUniformValue("normal_matrix", matrix.inverted().transposed());

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

void PolygonalCube::initShaders(){

    vShader.compileSourceFile(":/vshader.glsl");
    fShader.compileSourceFile(":/fshader.glsl");


}

void PolygonalCube::initGeometry(VertexData vertices[], GLuint indices[], int vertSize, int indSize, GLenum mode_){
    indicesSize = indSize;
    mode = mode_;

    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertSize * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, indSize * sizeof(GLuint));
}
