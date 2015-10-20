#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QOpenGLShaderProgram>
#include <string>

class LightSource
{
public:
    LightSource(){
    };

    virtual ~LightSource(){};
    virtual void load(QOpenGLShaderProgram *program, std::string valueName) = 0;
};

#endif // LIGHTSOURCE_H
