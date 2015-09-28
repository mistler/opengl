#include "sphere.h"

#include <cmath>
#include <iostream>
#include <time.h>
#include <stdlib.h>

Sphere::Sphere(int numberOfPoints)
{
    t = numberOfPoints;
    vertices = 2 * (t + 1) * t * 3;
    indexes = 4 * t * t + 2 * t;
    vertexArray = new GLfloat[vertices];
    colorArray = new GLfloat[vertices];
    indexArray = new GLuint[indexes];
    double d = (double)M_PI / t;
    int k = 0;
    double i = 0.;
    double j = 0.;

    srand(time(NULL));

    for(int iter = 0; iter <= t; iter++){
        double sini = sin(i);
        double cosi = cos(i);
        for(int jter = 0; jter < 2 * t; jter++){
            colorArray[k] = (rand() % 256) / 256.;
            vertexArray[k++] = sini * cos(j);
            colorArray[k] = (rand() % 256) / 256.;
            vertexArray[k++] = cosi;
            colorArray[k] = (rand() % 256) / 256.;
            vertexArray[k++] = sin(j) * sini;
            j += d;
        }
        i += d;
    }
    k = 0;
    for(int i = 0; i < t; i++){
        for(int j = 0; j < 2 * t; j++){
            indexArray[k++] = j + i * 2 * t;
            indexArray[k++] = j + (i + 1) * 2 * t;
        }
        indexArray[k++] = i * 2 * t;
        indexArray[k++] = (i + 1) * 2 * t;
    }

}

Sphere::~Sphere()
{
    delete[] vertexArray;
    delete[] colorArray;
    delete[] indexArray;
}

void Sphere::render()
{
    glVertexPointer(3, GL_FLOAT, 0, vertexArray);
    glColorPointer(3, GL_FLOAT, 0, colorArray);
    glDrawElements(GL_TRIANGLE_STRIP, indexes, GL_UNSIGNED_INT, indexArray);
}
