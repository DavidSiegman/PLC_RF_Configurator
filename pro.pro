#-------------------------------------------------
#
# Project created by QtCreator 2013-08-19T22:59:57
#
#-------------------------------------------------

QT      += core gui
QT      += serialport
QT      += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport


TARGET   = RF_PLC_Configurator
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
    MONITOR/monitorclass.h \
    SI4463/si4463_propertys_tablemodel.h \
    TCP/tcp.h \
    FILE/parceclass.h

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
    MONITOR/monitorclass.cpp \
    SI4463/si4463_propertys_tablemodel.cpp \
    TCP/tcp.cpp \
    FILE/parceclass.cpp

FORMS += \
    mainwindow.ui
