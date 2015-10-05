#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"

class Sphere: public Mesh
{
public:
    Sphere(int numberOfPoints);
    ~Sphere();

private:

    int vertices;
    int indices;

    VertexData* vertArray;
    GLuint* indArray;
};

#endif // SPHERE_H
