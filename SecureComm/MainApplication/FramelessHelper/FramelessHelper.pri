QT += winextras

INCLUDEPATH += $$PWD
LIBS += -lUser32

HEADERS += \
    $$PWD/FramelessHelper.h \
    $$PWD/FramelessHelper_p.h
SOURCES += \
    $$PWD/FramelessHelper.cpp

HEADERS += \
    $$PWD/Kernels/NativeWindowFilter.h \
    $$PWD/Kernels/NativeWindowFilter_p.h \
    $$PWD/Kernels/NativeWindowHelper.h \
    $$PWD/Kernels/NativeWindowHelper_p.h
SOURCES += \
    $$PWD/Kernels/NativeWindowFilter.cpp \
    $$PWD/Kernels/NativeWindowHelper.cpp
