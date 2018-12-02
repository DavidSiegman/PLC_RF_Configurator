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
    WINDOWS_FORMS/mainwindow.h \
    OTHER_FUNCTIONS/mess_enum.h \
    BUTTONS_HANDLERS/connecthandlerclass.h \
    MODEM/modemclass.h \
    GRAPH/mygraphgrid.h \
    GRAPH/mygraphlegend.h \
    GRAPH/mygraphscene.h \
    GRAPH/mypoligon.h \
    MONITOR/monitorclass.h \
    SI4463/si4463_propertys_tablemodel.h \
    TCP/tcp.h \
    FILE/parceclass.h \
    STYLE/style.h \
    SI4432/si4432class.h \
    FILTER/filter.h \
    PLC/plcclass.h \
    UPDATE/update.h \
    CRC/crc32_class.h \
    OTHER_FUNCTIONS/barr_to_string.h \
    ANDROID_FORMS/connections_form.h \
    ANDROID_FORMS/settings_form.h \
    ANDROID_FORMS/open_connection_form.h \
    ANDROID_FORMS/hands_enter_form.h \
    ANDROID_FORMS/net_settings_form.h \
    ANDROID_FORMS/plc_settings_form.h \
    ANDROID_FORMS/si4432_settings_form.h \
    ANDROID_FORMS/sniffer_settings_form.h \
    MODEM/firmwareinformationclass.h \
    MODEM/retranslatorpropertiesclass.h \
    MODEM/snifferpropertiesclass.h \
    MODEM/modempropertiesclass.h \
    SI4432/si4432configurationclass.h \
    ANDROID_FORMS/si4463_settings_form.h \
    RESIZE_CALCULATING/resizecalculating.h \
    ANDROID_FORMS/firmware_updating_form.h \
    ANDROID_FORMS/retranslation_table_form.h \

SOURCES += \
    COM/port.cpp \
    CRC/crc16_class.cpp \
    DATALOGIC/datalogic_class.cpp \
    SI4463/si4463class.cpp \
    MAIN/main.cpp \
    WINDOWS_FORMS/mainwindow.cpp \
    BUTTONS_HANDLERS/connecthandlerclass.cpp \
    MODEM/modemclass.cpp \
    GRAPH/mygraphgrid.cpp \
    GRAPH/mygraphlegend.cpp \
    GRAPH/mygraphscene.cpp \
    GRAPH/mypoligon.cpp \
    MONITOR/monitorclass.cpp \
    SI4463/si4463_propertys_tablemodel.cpp \
    TCP/tcp.cpp \
    FILE/parceclass.cpp \
    STYLE/style.cpp \
    SI4432/si4432class.cpp \
    FILTER/filter.cpp \
    PLC/plcclass.cpp \
    UPDATE/update.cpp \
    CRC/crc32_class.cpp \
    ANDROID_FORMS/connections_form.cpp \
    ANDROID_FORMS/settings_form.cpp \
    ANDROID_FORMS/open_connection_form.cpp \
    ANDROID_FORMS/hands_enter_form.cpp \
    OTHER_FUNCTIONS/barr_to_string.cpp \
    ANDROID_FORMS/net_settings_form.cpp \
    ANDROID_FORMS/plc_settings_form.cpp \
    ANDROID_FORMS/si4432_settings_form.cpp \
    ANDROID_FORMS/sniffer_settings_form.cpp \
    MODEM/firmwareinformationclass.cpp \
    MODEM/retranslatorpropertiesclass.cpp \
    MODEM/snifferpropertiesclass.cpp \
    MODEM/modempropertiesclass.cpp \
    SI4432/si4432configurationclass.cpp \
    ANDROID_FORMS/si4463_settings_form.cpp \
    RESIZE_CALCULATING/resizecalculating.cpp \
    ANDROID_FORMS/firmware_updating_form.cpp \
    ANDROID_FORMS/retranslation_table_form.cpp

FORMS += \
    WINDOWS_FORMS/mainwindow.ui \
    ANDROID_FORMS/connections_form.ui \
    ANDROID_FORMS/settings_form.ui \
    ANDROID_FORMS/open_connection_form.ui \
    ANDROID_FORMS/hands_enter_form.ui \
    ANDROID_FORMS/net_settings_form.ui \
    ANDROID_FORMS/plc_settings_form.ui \
    ANDROID_FORMS/si4432_settings_form.ui \
    ANDROID_FORMS/sniffer_settings_form.ui \
    ANDROID_FORMS/si4463_settings_form.ui \
    ANDROID_FORMS/firmware_updating_form.ui \
    ANDROID_FORMS/retranslation_table_form.ui

RESOURCES += \
    RESOURCES/images.qrc
