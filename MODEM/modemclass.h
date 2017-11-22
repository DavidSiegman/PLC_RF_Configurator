#ifndef MODEMCLASS_H
#define MODEMCLASS_H

#include <QObject>

class MODEMClass : public QObject
{
    Q_OBJECT
public:
    explicit MODEMClass(QObject *parent = 0);
    uchar    curr_ver, SWITCH_MODE, SwitchTable_element_index;
    uint     SWITCH_LEVEL, SWITCH_TIMEOUT, RX_TIMEOUT, TX_TIMEOUT, LED_LOGIC, CRC_CHECK_DISABLE;
    uint     RESET_DEVICE_TIMEOUT,UP_LINC, DIRECT_RET, BROADCAST, SNIFER_MODE;
    QString  boot_ver,fw_ver;
    double   BOOT_VERSION, FW_VERSION, BOOT_VERSION_SNIFER, FW_VERSION_SNIFER;
    QList<QString> SwitchTable;
private:

signals:

public slots:
};

#endif // MODEMCLASS_H
