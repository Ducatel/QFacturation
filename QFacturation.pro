#-------------------------------------------------
#
# Project created by QtCreator 2012-04-13T13:46:07
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += sql
QT       +=webkit

TARGET = QFacturation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    configwindow.cpp \
    aboutframe.cpp \
    customer.cpp \
    product.cpp \
    productdocument.cpp \
    document.cpp \
    newcustomerwindow.cpp \
    newproductwindow.cpp \
    searchwindow.cpp \
    newdocumentwindow.cpp \
    validdocument.cpp \
    paymenttypewindow.cpp \
    edittemplatewindow.cpp \
    balisetemplateframe.cpp

HEADERS  += mainwindow.h \
    main.h \
    configwindow.h \
    aboutframe.h \
    customer.h \
    product.h \
    productdocument.h \
    document.h \
    newcustomerwindow.h \
    newproductwindow.h \
    searchwindow.h \
    newdocumentwindow.h \
    validdocument.h \
    paymenttypewindow.h \
    edittemplatewindow.h \
    balisetemplateframe.h

TRANSLATIONS = qfacturation_en.ts
