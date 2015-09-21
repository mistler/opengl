#include "rgbcube.h"

RgbCube::RgbCube(){
    cubeVertexArray = new GLfloat[24]{0.0, 0.0, 1.0,
            0.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 0.0, 1.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            1.0, 1.0, 0.0,
            1.0, 0.0, 0.0};
    cubeColorArray = new GLfloat[24]{0.0, 0.0, 1.0,
            0.0, 1.0, 1.0,
            0.0, 0.0, 0.0,
            1.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
            0.0, 1.0, 0.0,
            1.0, 1.0, 0.0,
            1.0, 0.0, 0.0};
    cubeIndexArray = new GLubyte[24]{0,3,2,1,
            0,1,5,4,
            7,4,5,6,
            3,7,6,2,
            1,2,6,5,
            0,4,7,3};
}

void RgbCube::show(){

    glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
    glColorPointer(3, GL_FLOAT, 0, cubeColorArray);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndexArray);

}

RgbCube::~RgbCube(){
    delete[] cubeVertexArray;
    delete[] cubeColorArray;
    delete[] cubeIndexArray;
}
