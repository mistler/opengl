#include "widget.h"

Widget::Widget(QWidget *parent)
    : QGLWidget(parent)
{
    resize(600, 600);
}

void Widget::initializeGL()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
}

void Widget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nHeight, nHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10., 10., -10., 10., -10.0, 10.0);
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    currentWidth = nWidth;
    currentHeight = nHeight;
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glPushMatrix();
    glRotatef(yAxisRotation, 0.0, 1.0, 0.0);
    glRotatef(xAxisRotation, 1.0, 0.0, 0.0);
    glTranslatef(-0.5f, -0.5f, -0.5f);
    rgbCube[0].show();
    glTranslatef(0.f, 4.f, 0.f);
    rgbCube[1].show();
    glRotatef(yAxisRotation, 0.0, 1.0, 0.0);
    glRotatef(xAxisRotation, 1.0, 0.0, 0.0);
    glTranslatef(0.f, 2.f, 0.f);
    rgbCube[2].show();
    glPopMatrix();


}

void Widget::mousePressEvent(QMouseEvent *event)
{
    pressPosition = event->pos();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    xAxisRotation += (180 * ((GLfloat)event->y() - (GLfloat)pressPosition.y())) / (currentHeight);
    yAxisRotation += (180 * ((GLfloat)event->x() - (GLfloat)pressPosition.x())) / (currentWidth);

    pressPosition = event->pos();

    updateGL();
}
