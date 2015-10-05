#include "meshes/polygonalcube.h"

PolygonalCube::PolygonalCube(int n){

    N = n;

    vertices = (n + 1) * (n + 1) * 6;
    indices = (n + 1) * (2 * (n + 1) + 2) * 6;

    vertArray = new VertexData[vertices];
    indArray = new GLuint[indices];


    initSide(vertArray + (N+1) * (N+1) * 0, indArray + (N+1)*((N+1) * 2 + 2) * 0,  1.0f, -1.0f, -1.0f,
             -1.0f / n * 2,  1.0f / n * 2,  0.0f         , (N+1) * (N+1) * 0);
    initSide(vertArray + (N+1) * (N+1) * 1, indArray + (N+1)*((N+1) * 2 + 2) * 1, -1.0f,  1.0f, -1.0f,
              1.0f / n * 2,  0.0f        ,  1.0f / n * 2, (N+1) * (N+1) * 1);
    initSide(vertArray + (N+1) * (N+1) * 2, indArray + (N+1)*((N+1) * 2 + 2) * 2, -1.0f,  1.0f,  1.0f,
              1.0f / n * 2, -1.0f / n * 2,  0.0f        , (N+1) * (N+1) * 2);

    initGeometry(vertArray, indArray, vertices, indices, GL_TRIANGLE_STRIP);

}

PolygonalCube::~PolygonalCube(){
    delete[] vertArray;
    delete[] indArray;
}

void PolygonalCube::initSide(VertexData* data, GLuint* ind, float x, float y, float z, float dx, float dy, float dz, int offset){
    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= N; j++){
            if(dx == 0){
                data[i * (N+1) + j] = {QVector3D(x, y + dy * i, z + dz * j), QVector2D(0.0f, 0.0f)};
            }
            if(dy == 0){
                data[i * (N+1) + j] = {QVector3D(x + dx * i, y, z + dz * j), QVector2D(0.0f, 0.0f)};
            }
            if(dz == 0){
                data[i * (N+1) + j] = {QVector3D(x + dx * j, y + dy * i, z), QVector2D(0.0f, 0.0f)};
            }
        }
    }
    int k = 0;
    for(int i = 0; i <= N; i++){
        indArray[k++] = i * (N+1) + offset;
        for(int j = 0; j <= N; j++){
            indArray[k++] = j + i * (N+1) + offset;
            indArray[k++] = j + (i + 1) * (N+1) + offset;
        }
        indArray[k++] = (i + 1) * (N+1) + N + offset;
    }
}
