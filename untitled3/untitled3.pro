QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    archived_tasks.cpp \
    comment_sectionoftask.cpp \
    edit_org.cpp \
    edit_pro.cpp \
    edit_task.cpp \
    edit_team.cpp \
    forgetpass.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    new_org.cpp \
    new_pro.cpp \
    new_task.cpp \
    new_team.cpp \
    org_manager.cpp \
    project_manager.cpp \
    signin.cpp \
    task_manager.cpp \
    taski.cpp \
    team_manager.cpp \
    usermanager.cpp

HEADERS += \
    archived_tasks.h \
    comment_sectionoftask.h \
    edit_org.h \
    edit_pro.h \
    edit_task.h \
    edit_team.h \
    forgetpass.h \
    login.h \
    mainwindow.h \
    new_org.h \
    new_pro.h \
    new_task.h \
    new_team.h \
    org_manager.h \
    project_manager.h \
    signin.h \
    task_manager.h \
    taski.h \
    team_manager.h \
    usermanager.h

FORMS += \
    archived_tasks.ui \
    comment_sectionoftask.ui \
    edit_org.ui \
    edit_pro.ui \
    edit_task.ui \
    edit_team.ui \
    forgetpass.ui \
    login.ui \
    mainwindow.ui \
    new_org.ui \
    new_pro.ui \
    new_task.ui \
    new_team.ui \
    signin.ui \
    taski.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    stylesheet.qrc

DISTFILES += \
    ../../../Toolery/Toolery.qss
