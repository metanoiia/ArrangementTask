QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cell/cell.cpp \
    graphicsView/graphicsview.cpp \
    inputDataManager/inputdatamanager.cpp \
    main/main.cpp \
    main/mainwindow.cpp \
    target/target.cpp

HEADERS += \
    cell/cell.h \
    graphicsItem/graphicsitem.h \
    graphicsView/graphicsview.h \
    inputDataManager/inputdatamanager.h \
    main/mainwindow.h \
    target/target.h

FORMS += \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

