TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Body2D.c \
        DataStructs/Array1D.c \
        DataStructs/Array2D.c \
        DataStructs/List.c \
        DataStructs/QuadTree.c \
        Math/Shape2D.c \
        World2D.c \
        main.c

DISTFILES += \
    README.md

HEADERS += \
    Math/Rect2D.h \
    Math/Shape2D.h \
    Math/Transform2D.h \
    Math/Vector2D.h \
    DataStructs/List.h \
    DataStructs/AABB.h \
    DataStructs/Array1D.h \
    DataStructs/Array2D.h \
    DataStructs/QuadTree.h \
    Utils.h \
    Body2D.h \
    World2D.h

INCLUDEPATH += \
    $PWD/Math \
    $PWD/DataStructs \
    $PWD/
