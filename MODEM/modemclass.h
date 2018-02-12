#ifndef MODEMCLASS_H
#define MODEMCLASS_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include "ui_mainwindow.h"

typedef union RF_Switch_Mask_Type {
struct
{
    union
    {
       struct
       {
         volatile unsigned char LVL8: 2;
         volatile unsigned char LVL5: 3;
         volatile unsigned char LVL4: 3;
         volatile unsigned char LVL1: 4;
         volatile unsigned char LVL0: 4;
       }Field;
       unsigned char Bytes[2];
    } Retranslation_MASK_0;
    union
    {
       struct
       {
         volatile unsigned char LVL9: 2;
         volatile unsigned char LVL7: 3;
         volatile unsigned char LVL6: 3;
         volatile unsigned char LVL3: 4;
         volatile unsigned char LVL2: 4;
       }Field;
       unsigned char Bytes[2];
    } Retranslation_MASK_1;
}Field;
}RF_Switch_Mask;


class MODEMClass : public QObject
{
    Q_OBJECT
public:
    explicit MODEMClass(Ui::MainWindow *ui,QObject *parent = 0);
    uchar    curr_ver, SWITCH_MODE;
    uint     SWITCH_TIMEOUT, RX_TIMEOUT, TX_TIMEOUT, LED_LOGIC, CRC_CHECK_DISABLE;
    uint     RESET_DEVICE_TIMEOUT,UP_LINC, DIRECT_RET, BROADCAST, SNIFER_MODE;
    QString  boot_ver,fw_ver;
    RF_Switch_Mask* SWITCH_MASK, *SWITCH_MASK_DESTINATION;
    double   BOOT_VERSION, FW_VERSION, BOOT_VERSION_SNIFER, FW_VERSION_SNIFER;
    QList<QString> SwitchTable;
private:
    Ui::MainWindow     *ui;
    QStandardItemModel *model;
    uchar current_index;
    uint  SWITCH_LEVEL;
signals:

public slots:
    void addNewItem(QString string);
    void delNewItem();
    void setCurrent_Index(uchar index);
    uchar getCurrent_Index();
    void clearNetTable();
    void setSWITCH_LEVEL(uint);
    uint getSWITCH_LEVEL(void);
};

#endif // MODEMCLASS_H
