#ifndef SPOTLIGHTSOURCE_H
#define SPOTLIGHTSOURCE_H


#include "lightsource.h"

class SpotLightSource : public LightSource
{
public:
    SpotLightSource(QVector4D position, QVector4D direction, QVector4D diffuse, QVector4D ambient, QVector4D specular, float inner, float outer, float attenuation): pos(position), dif(diffuse), amb(ambient), spe(specular), att(attenuation), dir(direction), inn(inner), out(outer){
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
        program->setUniformValue((valueName + "type").c_str(), 2);

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

#endif // SPOTLIGHTSOURCE_H
