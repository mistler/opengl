#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include <QGLWidget>

#include "rgbcube.h"

class Widget : public QGLWidget
{
public:
    Widget(QWidget *parent = 0);

protected:
   void initializeGL();
   void resizeGL(int nWidth, int nHeight);
   void paintGL();
   void mouseMoveEvent(QMouseEvent *event);
   void mousePressEvent(QMouseEvent *event);

private:
    QPoint pressPosition;
    QPoint releasePosition;
    GLfloat xAxisRotation;
    GLfloat yAxisRotation;
    GLfloat currentWidth;
    GLfloat currentHeight;

    RgbCube rgbCube[30];
    //RgbCube rotatingCube;
    //RgbCube doubleRotatingCube;

};



#endif // WIDGET_H
