#ifndef POLYGONALCUBE_H
#define POLYGONALCUBE_H

#include "mesh.h"

class PolygonalCube : public Mesh
{
public:
    PolygonalCube(int n);
    ~PolygonalCube();

private:
    void initSide(VertexData* data, GLuint* ind, float x, float y, float z, float dx, float dy, float dz, int offset);

private:
    int N;
    int vertices;
    int indices;

    VertexData* vertArray;
    GLuint* indArray;
};

#endif // POLYGONALCUBE_H
