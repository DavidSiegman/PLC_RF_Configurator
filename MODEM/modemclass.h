#ifndef MODEMCLASS_H
#define MODEMCLASS_H

#include <QObject>

class MODEMClass : public QObject
{
    Q_OBJECT
public:
    explicit MODEMClass(QObject *parent = 0);
    uchar    curr_ver, SWITCH_MODE;
    uint     SWITCH_LEVEL, SWITCH_TIMEOUT, RX_TIMEOUT, TX_TIMEOUT, LED_LOGIC, CRC_CHECK_DISABLE, UP_LINC, DIRECT_RET, BROADCAST;
    QString  boot_ver,fw_ver;
    double   BOOT_VERSION, FW_VERSION;
private:

signals:

public slots:
};

#endif // MODEMCLASS_H
