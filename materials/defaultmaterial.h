#ifndef DEFAULTMATERIAL_H
#define DEFAULTMATERIAL_H

#include "material.h"

class DefaultMaterial : public Material{
public:
    DefaultMaterial();
    virtual void load(QOpenGLShaderProgram *program){

    }
};

#endif // DEFAULTMATERIAL_H
