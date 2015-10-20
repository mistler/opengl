#ifndef LIGHT_H
#define LIGHT_H

#include <QOpenGLShaderProgram>
#include <vector>
#include <string>

#include "lightsource.h"

class Light
{
public:

    Light(){
        char tmp[] = "lightSource[0].";
        for(int i = 0; i < MAX_LIGHTS; i++){
            tmp[12] = i + '0';
            valueNames.push_back(std::string(tmp));
        }
    }

    virtual ~Light(){
        for(std::vector<LightSource*>::iterator i = lightSources.begin(); i != lightSources.end(); i++){
            delete *i;
        }
    }

    virtual void addLightSource(LightSource* lightSource){
        lightSources.push_back(lightSource);
    }

    virtual void load(QOpenGLShaderProgram *program){
        int k = 0;
        program->setUniformValue("lights", (int)lightSources.size());
        for(std::vector<LightSource*>::iterator i = lightSources.begin(); i != lightSources.end(); i++){
            (*i)->load(program, valueNames[k++]);
        }
    }

private:
    const int MAX_LIGHTS = 5;

    std::vector<LightSource*> lightSources;
    std::vector<std::string> valueNames;
};

#endif // LIGHT_H
