
QT       += core gui opengl
LIBS += -lopengl32

TARGET = mistler
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    rgbcube.cpp \
    mesh.cpp \
    sphere.cpp

HEADERS  += widget.h \
    rgbcube.h \
    mesh.h \
    sphere.h
