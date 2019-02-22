#ifndef MODEMCLASS_H
#define MODEMCLASS_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include "firmwareinformationclass.h"
#include "retranslatorpropertiesclass.h"
#include "snifferpropertiesclass.h"
#include "modempropertiesclass.h"
#include "plcrfmodempropertiesclass.h"
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

    PlcRfModemPropertiesClass    *In_PLC_RF433_Modem_Properties;
    PlcRfModemPropertiesClass    *Out_PLC_RF433_Modem_Properties;

signals:
    void                          sIn_Firmware_Information        (FirmwareInformationClass*);
    void                          sIn_Retranslator_Properties     (RetranslatorPropertiesClass*);
    void                          sOut_Retranslator_Properties    (RetranslatorPropertiesClass*);
    void                          sIn_Sniffer_Properties          (SnifferPropertiesClass*);
    void                          sOut_Sniffer_Properties         (SnifferPropertiesClass*);
    void                          sIn_Modem_Properties            (ModemPropertiesClass*);
    void                          sOut_Modem_Properties           (ModemPropertiesClass*);
    void                          sIn_PLC_RF433_Modem_Properties  (PlcRfModemPropertiesClass*);
    void                          sOut_PLC_RF433_Modem_Properties (PlcRfModemPropertiesClass*);

public slots:
    FirmwareInformationClass*     getIn_Firmware_Information(void);
    void                          ChangedIn_Firmware_Information(void);
    RetranslatorPropertiesClass*  getIn_Retranslator_Properties(void);
    void                          ChangedIn_Retranslator_Properties(void);
    RetranslatorPropertiesClass*  getOut_Retranslator_Properties(void);
    void                          ChangedOut_Retranslator_Properties(void);
    SnifferPropertiesClass*       getIn_Sniffer_Properties(void);
    void                          ChangedIn_Sniffer_Properties(void);
    SnifferPropertiesClass*       getOut_Sniffer_Properties(void);
    void                          ChangedOut_Sniffer_Properties(void);
    ModemPropertiesClass*         getIn_Modem_Properties(void);
    void                          ChangedIn_Modem_Properties(void);
    ModemPropertiesClass*         getOut_Modem_Properties(void);
    void                          ChangedOut_Modem_Properties(void);
    PlcRfModemPropertiesClass*    getIn_PLC_RF433_Modem_Properties(void);
    void                          ChangedIn_PLC_RF433_Modem_Properties(void);
    PlcRfModemPropertiesClass*    getOut_PLC_RF433_Modem_Properties(void);
    void                          ChangedOut_PLC_RF433_Modem_Properties(void);

    void                          ClearAllData(void);

private slots:

};

#endif // MODEMCLASS_H
