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
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target
