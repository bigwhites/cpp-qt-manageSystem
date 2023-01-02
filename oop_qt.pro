QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    inputwidget.cpp \
    logindia.cpp \
    main.cpp \
    mainwindow.cpp \
    removeWindows.cpp \
    s/Beverage.cpp \
    s/Commodity.cpp \
    s/Cosmetic.cpp \
    s/Daily.cpp \
    s/Food.cpp \
    s/Manager.cpp \
    s/RepManager.cpp \
    s/Saler.cpp \
    s/Sorter.cpp

HEADERS += \
    head/Beverage.h \
    head/Commodity.h \
    head/Cosmetic.h \
    head/Daily.h \
    head/Food.h \
    head/Manager.h \
    head/RepManager.h \
    head/Saler.h \
    head/Sorter.h \
    head/commodities.h \
    inputwidget.h \
    logindia.h \
    mainwindow.h

FORMS += \
    inputwidget.ui \
    logindia.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc.qrc

DISTFILES +=
