TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Body2D.c \
        DataStructs/Array1D.c \
        DataStructs/List.c \
        DataStructs/QuadTree.c \
        World2D.c \
        main.c

DISTFILES += \
    README.md

HEADERS += \
    DataStructs/List.h \
    Math/Matrix2D.h \
    Math/Rect2D.h \
    Math/Shape2D.h \
    Math/Transform2D.h \
    Math/Vector2D.h \
    Body2D.h \
    DataStructs/AABB.h \
    DataStructs/Array1D.h \
    DataStructs/QuadTree.h \
    Utils.h \
    World2D.h

INCLUDEPATH += \
    $PWD/Math \
    $PWD/DataStructs \
    $PWD
