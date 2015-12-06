QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    mainwidget.cpp \
    meshes/geometryengine.cpp \
    meshes/rgbcube.cpp \
    meshes/sphere.cpp \
    meshes/polygonalcube.cpp \
    light.cpp \
    lightsource.cpp \
    material.cpp \
    materials/defaultmaterial.cpp \
    lights/pointlightsource.cpp \
    lights/directionallightsource.cpp \
    lights/spotlightsource.cpp \
    meshes/meshfromobj.cpp

HEADERS += \
    mainwidget.h \
    meshes/geometryengine.h \
    mesh.h \
    meshes/rgbcube.h \
    meshes/sphere.h \
    meshes/polygonalcube.h \
    light.h \
    lightsource.h \
    material.h \
    materials/defaultmaterial.h \
    lights/pointlightsource.h \
    lights/directionallightsource.h \
    lights/spotlightsource.h \
    meshes/meshfromobj.h

RESOURCES += \
    shaders/sphere/sphereshaders.qrc \
    shaders/polygonalcube/polygonalcubeshaders.qrc \
    textures.qrc \
    meshObjects.qrc

INSTALLS += target
