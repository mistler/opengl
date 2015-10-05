#include "meshes/sphere.h"

#include <cmath>
#include <iostream>
#include <time.h>
#include <stdlib.h>

Sphere::Sphere(int numberOfPoints){
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

Sphere::~Sphere(){
    delete[] vertArray;
    delete[] indArray;
}
