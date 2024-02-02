QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    new_org.cpp \
    org_manager.cpp \
    signin.cpp \
    taski.cpp \
    team_manager.cpp \
    usermanager.cpp

HEADERS += \
    login.h \
    mainwindow.h \
    new_org.h \
    org_manager.h \
    signin.h \
    taski.h \
    team_manager.h \
    usermanager.h

FORMS += \
    login.ui \
    mainwindow.ui \
    new_org.ui \
    signin.ui \
    taski.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
