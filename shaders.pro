QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    mainwidget.cpp \
    meshes/geometryengine.cpp \
    meshes/rgbcube.cpp \
    meshes/sphere.cpp \
    meshes/polygonalcube.cpp

HEADERS += \
    mainwidget.h \
    meshes/geometryengine.h \
    mesh.h \
    meshes/rgbcube.h \
    meshes/sphere.h \
    meshes/polygonalcube.h

RESOURCES += \
    shaders/sphere/sphereshaders.qrc \
    shaders/polygonalcube/polygonalcubeshaders.qrc \
    textures.qrc

INSTALLS += target
