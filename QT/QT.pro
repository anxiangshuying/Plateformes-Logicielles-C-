#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T08:30:59
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loginwindow.cpp \
    LoginController.cpp \
    aproposwindow.cpp \
    addpatientwindow.cpp \
    addpersonnelsoinswindow.cpp \
    patientmodel.cpp \
    personnelsoinsmodel.cpp \
    c_init_bd.cpp \
    databasecontroller.cpp \
    patientcontroller.cpp \
    personnelsoinscontroller.cpp \
    ShowController.cpp \
    judgecontroller.cpp \
    modifypatientwindow.cpp \
    modifypersonnelsoinswindow.cpp \
    PlanificationController.cpp \
    addradiologue.cpp

HEADERS  += mainwindow.h \
    loginwindow.h \
    aproposwindow.h \
    addpatientwindow.h \
    addpersonnelsoinswindow.h \
    patientmodel.h \
    personnelsoinsmodel.h \
    c_init_bd.h \
    databasecontroller.h \
    judgecontroller.h \
    patientcontroller.h \
    personnelsoinscontroller.h \
    modifypatientwindow.h \
    modifypersonnelsoinswindow.h \
    addradiologue.h

FORMS    += mainwindow.ui \
    loginwindow.ui \
    aproposwindow.ui \
    addpatientwindow.ui \
    addpersonnelsoinswindow.ui \
    modifypatientwindow.ui \
    modifypersonnelsoinswindow.ui \
    addradiologue.ui

RESOURCES += \
    Images.qrc
