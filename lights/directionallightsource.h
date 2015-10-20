#ifndef DIRECTIONALLIGHTSOURCE_H
#define DIRECTIONALLIGHTSOURCE_H

#include "lightsource.h"

class DirectionalLightSource : public LightSource
{
public:
    DirectionalLightSource(QVector4D direction, QVector4D color, QVector4D ambient): pos(0.0f,0.0f,0.0f,0.0f), dif(color), amb(ambient), spe(0.0f,0.0f,0.0f,0.0f), att(0.0f), dir(direction), inn(0.0f), out(0.0f){
    }

    virtual void load(QOpenGLShaderProgram *program, std::string valueName){
        program->setUniformValue((valueName + "position").c_str(), pos);
        program->setUniformValue((valueName + "diffuse").c_str(), dif);
        program->setUniformValue((valueName + "ambient").c_str(), amb);
        program->setUniformValue((valueName + "specular").c_str(), spe);
        program->setUniformValue((valueName + "direction").c_str(), dir);
        program->setUniformValue((valueName + "attenuation").c_str(), att);
        program->setUniformValue((valueName + "inner").c_str(), inn);
        program->setUniformValue((valueName + "outer").c_str(), out);
        program->setUniformValue((valueName + "type").c_str(), 0);
    }

private:
    QVector4D pos;
    QVector4D dif;
    QVector4D amb;
    QVector4D spe;
    QVector4D dir;
    float att;
    float inn;
    float out;
};

#endif // DIRECTIONALLIGHTSOURCE_H
