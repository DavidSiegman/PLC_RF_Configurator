#-------------------------------------------------
#
# Project created by QtCreator 2013-08-19T22:59:57
#
#-------------------------------------------------

QT       += core gui
QT      += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport


TARGET = my_shag
TEMPLATE = app

FORMS

HEADERS += \
    COM/port.h \
    CRC/crc16_class.h \
    DATALOGIC/datalogic_class.h \
    SI4463/si4463_propertys_type.h \
    SI4463/si4463class.h \
    mainwindow.h \
    mess_enum.h \
    BUTTONS_HANDLERS/connecthandlerclass.h \
    MODEM/modemclass.h \
    GRAPH/mygraphgrid.h \
    GRAPH/mygraphlegend.h \
    GRAPH/mygraphscene.h \
    GRAPH/mypoligon.h \
    MONITOR/monitorclass.h

SOURCES += \
    COM/port.cpp \
    CRC/crc16_class.cpp \
    DATALOGIC/datalogic_class.cpp \
    SI4463/si4463class.cpp \
    main.cpp \
    mainwindow.cpp \
    BUTTONS_HANDLERS/connecthandlerclass.cpp \
    MODEM/modemclass.cpp \
    GRAPH/mygraphgrid.cpp \
    GRAPH/mygraphlegend.cpp \
    GRAPH/mygraphscene.cpp \
    GRAPH/mypoligon.cpp \
    MONITOR/monitorclass.cpp

FORMS += \
    mainwindow.ui
