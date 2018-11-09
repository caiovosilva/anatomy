#-------------------------------------------------
#
# Project created by QtCreator 2018-10-19T16:21:22
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = anatomy
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    DAO/daoanatomyimagesqlite.cpp \
    DAO/daoanswersqlite.cpp \
    DAO/daoquestionsqlite.cpp \
    DAO/dbconnection.cpp \
    model/answer.cpp \
    model/question.cpp \
    model/anatomyimage.cpp \
    windows/listquestionswindow.cpp \
    windows/mainwindow.cpp \
    windows/newquestionwindow.cpp \
    windows/playwindow.cpp \
    model/modality.cpp \
    model/anatomicalregion.cpp \
    windows/entrieswindow.cpp \
    DAO/daomodalitysqlite.cpp \
    windows/newmodalitywindow.cpp \
    windows/newanatomicalregionwindow.cpp \
    DAO/daoanatomicalregionsqlite.cpp \
    windows/newanatomyimagewindow.cpp \
    model/assignment.cpp \
    DAO/daoassignmentsqlite.cpp \
    DAO/daoclass.cpp \
    windows/newassignmentwindow.cpp

HEADERS += \
    DAO/daoanatomyimage.h \
    DAO/daoanatomyimagesqlite.h \
    DAO/daoanswer.h \
    DAO/daoanswersqlite.h \
    DAO/daoquestion.h \
    DAO/daoquestionsqlite.h \
    DAO/dbconnection.h \
    model/answer.h \
    model/question.h \
    model/anatomyimage.h \
    windows/listquestionswindow.h \
    windows/mainwindow.h \
    windows/playwindow.h \
    windows/newquestionwindow.h \
    model/modality.h \
    model/anatomicalregion.h \
    windows/entrieswindow.h \
    DAO/daomodality.h \
    DAO/daomodalitysqlite.h \
    windows/newmodalitywindow.h \
    windows/newanatomicalregionwindow.h \
    DAO/daoanatomicalregion.h \
    DAO/daoanatomicalregionsqlite.h \
    windows/newanatomyimagewindow.h \
    model/assignment.h \
    DAO/daoassignment.h \
    DAO/daoassignmentsqlite.h \
    DAO/daoclass.h \
    windows/newassignmentwindow.h

FORMS += \
    mainwindow.ui \
    newquestionwindow.ui \
    listquestionswindow.ui \
    playwindow.ui \
    entrieswindow.ui \
    newmodalitywindow.ui \
    newanatomicalregionwindow.ui \
    newanatomyimagewindow.ui \
    newassignmentwindow.ui
