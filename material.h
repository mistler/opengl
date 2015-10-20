#ifndef MATERIAL_H
#define MATERIAL_H

#include <QOpenGLShaderProgram>

class Material
{
public:
    Material();
    virtual void load(QOpenGLShaderProgram *program) = 0;
};

#endif // MATERIAL_H
