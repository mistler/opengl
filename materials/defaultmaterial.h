#ifndef DEFAULTMATERIAL_H
#define DEFAULTMATERIAL_H

#include "material.h"

#include <QOpenGLTexture>

class DefaultMaterial : public Material{
public:
    DefaultMaterial(QOpenGLShaderProgram *program){

        texture = new QOpenGLTexture(QImage(":/1.jpg"));
        texture->setMinificationFilter(QOpenGLTexture::Nearest);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        texture->setWrapMode(QOpenGLTexture::Repeat);

        normal_map = new QOpenGLTexture(QImage(":/3.jpg"));
        normal_map->setMinificationFilter(QOpenGLTexture::Nearest);
        normal_map->setMagnificationFilter(QOpenGLTexture::Linear);
        normal_map->setWrapMode(QOpenGLTexture::Repeat);

        another_texture = new QOpenGLTexture(QImage(":/2.jpg"));
        another_texture->setMinificationFilter(QOpenGLTexture::Nearest);
        another_texture->setMagnificationFilter(QOpenGLTexture::Linear);
        another_texture->setWrapMode(QOpenGLTexture::Repeat);
    }

    ~DefaultMaterial(){
        delete texture;
        delete normal_map;
        delete another_texture;
    }

    virtual void load(QOpenGLShaderProgram *program){


        texture->bind(0);
        normal_map->bind(1);
        another_texture->bind(2);


        program->setUniformValue("normal_map", 1);
        program->setUniformValue("texture", 0);
        program->setUniformValue("another_texture", 2);



        program->setUniformValue("mater.ambient", QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
        program->setUniformValue("mater.diffuse", QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
        program->setUniformValue("mater.specular", QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
        program->setUniformValue("mater.shininess", 50.0f);

    }

private:
    QOpenGLTexture* texture;
    QOpenGLTexture* normal_map;
    QOpenGLTexture* another_texture;
};

#endif // DEFAULTMATERIAL_H
