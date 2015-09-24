#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include <QGLWidget>

#include "mesh.h"

class Widget : public QGLWidget
{
public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
   void initializeGL();
   void resizeGL(int nWidth, int nHeight);
   void paintGL();
   void makeFrustum(double fovY, double aspectRatio, double front, double back);
   void mouseMoveEvent(QMouseEvent *event);
   void mousePressEvent(QMouseEvent *event);

private:

   const int N = 3;
   const int SPHERE_TRIANGLES = 1000;

    QPoint pressPosition;
    QPoint releasePosition;
    GLfloat xAxisRotation;
    GLfloat yAxisRotation;
    GLfloat currentWidth;
    GLfloat currentHeight;

    Mesh** meshes;
    //RgbCube rotatingCube;
    //RgbCube doubleRotatingCube;

};



#endif // WIDGET_H
