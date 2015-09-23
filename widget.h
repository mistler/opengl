#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include <QGLWidget>

#include "mesh.h"
#include "rgbcube.h"

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

    QPoint pressPosition;
    QPoint releasePosition;
    GLfloat xAxisRotation;
    GLfloat yAxisRotation;
    GLfloat currentWidth;
    GLfloat currentHeight;

    Mesh** cubes;
    //RgbCube rotatingCube;
    //RgbCube doubleRotatingCube;

};



#endif // WIDGET_H
