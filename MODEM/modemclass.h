#ifndef MODEMCLASS_H
#define MODEMCLASS_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include "firmwareinformationclass.h"
#include "retranslatorpropertiesclass.h"
#include "snifferpropertiesclass.h"
#include "modempropertiesclass.h"
#include "ui_mainwindow.h"

class MODEMClass : public QObject
{
    Q_OBJECT
public:
    explicit MODEMClass(Ui::MainWindow *ui,QObject *parent = 0);
    explicit MODEMClass(QObject *parent = 0);

private:

    FirmwareInformationClass     *In_Firmware_Information;

    RetranslatorPropertiesClass  *In_Retranslator_Properties;
    RetranslatorPropertiesClass  *Out_Retranslator_Properties;

    SnifferPropertiesClass       *In_Sniffer_Properties;
    SnifferPropertiesClass       *Out_Sniffer_Properties;

    ModemPropertiesClass         *In_Modem_Properties;
    ModemPropertiesClass         *Out_Modem_Properties;

signals:

    void                          sIn_Firmware_Information    (FirmwareInformationClass*);
    void                          sIn_Retranslator_Properties (RetranslatorPropertiesClass*);
    void                          sOut_Retranslator_Properties(RetranslatorPropertiesClass*);
    void                          sIn_Sniffer_Properties      (SnifferPropertiesClass*);
    void                          sOut_Sniffer_Properties     (SnifferPropertiesClass*);
    void                          sIn_Modem_Properties        (ModemPropertiesClass*);
    void                          sOut_Modem_Properties       (ModemPropertiesClass*);

public slots:

    FirmwareInformationClass*     getIn_Firmware_Information(void);

    RetranslatorPropertiesClass*  getIn_Retranslator_Properties(void);

    RetranslatorPropertiesClass*  getOut_Retranslator_Properties(void);

    SnifferPropertiesClass*       getIn_Sniffer_Properties(void);

    SnifferPropertiesClass*       getOut_Sniffer_Properties(void);

    ModemPropertiesClass*         getIn_Modem_Properties(void);

    ModemPropertiesClass*         getOut_Modem_Properties(void);

private slots:

};

#endif // MODEMCLASS_H
