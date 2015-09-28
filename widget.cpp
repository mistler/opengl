#include "widget.h"


Widget::Widget(QWidget *parent)
    : QGLWidget(parent)
{
    resize(600, 600);
    cubes = new Mesh*[N];
    for(int i = 0; i < N; i++){
        cubes[i] = new RgbCube();
    }
}

Widget::~Widget(){
    for(int i = 0; i < N; i++){
        delete cubes[i];
    }
    delete[] cubes;
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
    //glOrtho(-5., 5., -5., 5., -5., 5.);
    glFrustum(-1.0, 1.0,
              -1.0, 1.0,
             2., 20.0);
    currentWidth = nWidth;
    currentHeight = nHeight;
    glTranslatef(.0f, .0f, -13.f);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glRotatef(yAxisRotation, 0.0, 1.0, 0.0);
    glRotatef(xAxisRotation, 1.0, 0.0, 0.0);
    glTranslatef(-0.5f, -0.5f, -0.5f);
    cubes[0]->render();
    glTranslatef(0.f, 4.f, 0.f);
    cubes[1]->render();
    glRotatef(yAxisRotation, 0.0, 1.0, 0.0);
    glRotatef(xAxisRotation, 1.0, 0.0, 0.0);
    glTranslatef(0.f, 2.f, 0.f);
    cubes[2]->render();
}

void Widget::makeFrustum(double fovY, double aspectRatio, double front, double back)
{
    const double DEG2RAD = 3.14159265 / 180;

    double tangent = tan(fovY/2 * DEG2RAD);   // tangent of half fovY
    double height = front * tangent;          // half height of near plane
    double width = height * aspectRatio;      // half width of near plane

    // params: left, right, bottom, top, near, far
    glFrustum(-width, width, -height, height, front, back);
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
