#ifndef POINTLIGHTSOURCE_H
#define POINTLIGHTSOURCE_H

#include "lightsource.h"


class PointLightSource : public LightSource{
public:
    PointLightSource(QVector4D position, QVector4D diffuse, QVector4D ambient, QVector4D specular, float attenuation): pos(position), dif(diffuse), amb(ambient), spe(specular), att(attenuation), dir(0.0f, 0.0f, 0.0f, 0.0f), inn(0.0f), out(0.0f){
    }

    virtual void load(QOpenGLShaderProgram *program, std::string valueName){
        GLint type = 1;
        program->setUniformValue((valueName + "type").c_str(), type);
        program->setUniformValue((valueName + "position").c_str(), pos);
        program->setUniformValue((valueName + "diffuse").c_str(), dif);
        program->setUniformValue((valueName + "ambient").c_str(), amb);
        program->setUniformValue((valueName + "specular").c_str(), spe);
        program->setUniformValue((valueName + "direction").c_str(), dir);
        program->setUniformValue((valueName + "attenuation").c_str(), att);
        program->setUniformValue((valueName + "inner").c_str(), inn);
        program->setUniformValue((valueName + "outer").c_str(), out);

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

#endif // POINTLIGHTSOURCE_H
