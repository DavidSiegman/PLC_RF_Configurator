#ifndef MODEMCLASS_H
#define MODEMCLASS_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include "ui_mainwindow.h"

#define PLC_MODEM         "PLC_MODEM"
#define RF_MODEM_SI4432   "RF_MODEM_SI4432"
#define RF_MODEM_SI4463   "RF_MODEM_SI4463"
#define RF_SNIFFER_SI4432 "RF_SNIFFER_SI4432"
#define RF_SNIFFER_SI4463 "RF_SNIFFER_SI4463"
#define RF_PLC_MODEM      "RF_PLC_MODEM"
#define RF_PLC_SNIFFER    "RF_PLC_SNIFFER"
#define TERMINAL          "TERMINAL"

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

typedef struct MODEMClass_Propertys_Type
{

    uchar           CURRENT_FIRMWARE_VERSION;
    QString         String_BOOTLOADER_VERSION;
    QString         String_UPGRADABLE_VERSION;
    double          BOOTLOADER_VERSION;
    double          UPGRADABLE_VERSION;
    double          BOOTLOADER_VERSION_SNIFER;
    double          UPGRADABLE_VERSION_SNIFER;
    double          BOOTLOADER_VERSION_TERMINAL;
    double          UPGRADABLE_VERSION_TERMINAL;
    uint            BOOTLOADER_SIZE;
    uint            UPGRADABLE_SIZE;
    QByteArray      BOOTLOADER_CRC32;
    QByteArray      UPGRADABLE_CRC32;

    uchar           SWITCH_MODE;
    uint            SWITCH_TIMEOUT;
    uint            SWITCH_LEVEL;
    uint            SWITCH_LEVEL_DESTINATION;

    uint            RX_TIMEOUT;
    uint            TX_TIMEOUT;
    uchar           LED_LOGIC;
    uchar           CRC_CHECK_DISABLE;
    uint            RESET_DEVICE_TIMEOUT;
    uchar           UP_LINC;
    uchar           DIRECT_RET;
    uint            BROADCAST;
    uchar           SNIFER_MODE;

    RF_Switch_Mask  *SWITCH_MASK;
    RF_Switch_Mask  *SWITCH_MASK_DESTINATION;

    QString         Device_Name;

    QList<QString>  SwitchTable;

}MODEMClass_Propertys;

class MODEMClass : public QObject
{
    Q_OBJECT
public:
    explicit MODEMClass(Ui::MainWindow *ui,QObject *parent = 0);
    explicit MODEMClass(QObject *parent = 0);

private:
    QStandardItemModel *model;
    uchar current_index;

    MODEMClass_Propertys MODEM_Propertys;

signals:
    void CURRENT_FIRMWARE_VERSION (uchar);
    void String_BOOTLOADER_VERSION(QString);
    void String_UPGRADABLE_VERSION(QString);
    void BOOTLOADER_VERSION(double);
    void UPGRADABLE_VERSION(double);
    void BOOTLOADER_VERSION_SNIFER(double);
    void UPGRADABLE_VERSION_SNIFER(double);
    void BOOTLOADER_VERSION_TERMINAL(double);
    void UPGRADABLE_VERSION_TERMINAL(double);
    void BOOTLOADER_SIZE(uint);
    void UPGRADABLE_SIZE(uint);
    void BOOTLOADER_CRC32(QByteArray);
    void UPGRADABLE_CRC32(QByteArray);
    void SWITCH_MODE(uchar);
    void SWITCH_TIMEOUT(uint);
    void SWITCH_LEVEL(uint);
    void SWITCH_LEVEL_DESTINATION(uint);
    void RX_TIMEOUT(uint);
    void TX_TIMEOUT(uint);
    void LED_LOGIC(uchar);
    void CRC_CHECK_DISABLE(uchar);
    void RESET_DEVICE_TIMEOUT(uint);
    void UP_LINC(uchar);
    void DIRECT_RET(uchar);
    void BROADCAST(uint);
    void SNIFER_MODE(uchar);
    void Device_Name(QString);

public slots:
    void       addNewItem(QString);
    void       delNewItem();
    void       clearNetTable();

    MODEMClass_Propertys getMODEM_Propertys(void);
    void setMODEM_Propertys(MODEMClass_Propertys);

    uchar      getCurrent_Index(void);
    void       setCurrent_Index(uchar);

    uchar      getCURRENT_FIRMWARE_VERSION(void);
    void       setCURRENT_FIRMWARE_VERSION(uchar);

    QString    getString_BOOTLOADER_VERSION(void);
    void       setString_BOOTLOADER_VERSION(QString);

    QString    getString_UPGRADABLE_VERSION(void);
    void       setString_UPGRADABLE_VERSION(QString);

    double     getBOOTLOADER_VERSION(void);
    void       setBOOTLOADER_VERSION(double);

    double     getUPGRADABLE_VERSION(void);
    void       setUPGRADABLE_VERSION(double);

    double     getBOOTLOADER_VERSION_SNIFER(void);
    void       setBOOTLOADER_VERSION_SNIFER(double);

    double     getUPGRADABLE_VERSION_SNIFER(void);
    void       setUPGRADABLE_VERSION_SNIFER(double);

    double     getBOOTLOADER_VERSION_TERMINAL(void);
    void       setBOOTLOADER_VERSION_TERMINAL(double);

    double     getUPGRADABLE_VERSION_TERMINAL(void);
    void       setUPGRADABLE_VERSION_TERMINAL(double);

    uint       getBOOTLOADER_SIZE(void);
    void       setBOOTLOADER_SIZE(uint);

    uint       getUPGRADABLE_SIZE(void);
    void       setUPGRADABLE_SIZE(uint);

    QByteArray getBOOTLOADER_CRC32(void);
    void       setBOOTLOADER_CRC32(QByteArray);

    QByteArray getUPGRADABLE_CRC32(void);
    void       setUPGRADABLE_CRC32(QByteArray);

    uchar      getSWITCH_MODE(void);
    void       setSWITCH_MODE(uchar);

    uint       getSWITCH_TIMEOUT(void);
    void       setSWITCH_TIMEOUT(uint);

    uint       getSWITCH_LEVEL(void);
    void       setSWITCH_LEVEL(uint);

    uint       getSWITCH_LEVEL_DESTINATION(void);
    void       setSWITCH_LEVEL_DESTINATION(uint);

    uint       getRX_TIMEOUT(void);
    void       setRX_TIMEOUT(uint);

    uint       getTX_TIMEOUT(void);
    void       setTX_TIMEOUT(uint);

    uchar      getLED_LOGIC(void);
    void       setLED_LOGIC(uchar);

    uchar      getCRC_CHECK_DISABLE(void);
    void       setCRC_CHECK_DISABLE(uchar);

    uint       getRESET_DEVICE_TIMEOUT(void);
    void       setRESET_DEVICE_TIMEOUT(uint);

    uchar      getUP_LINC(void);
    void       setUP_LINC(uchar);

    uchar      getDIRECT_RET(void);
    void       setDIRECT_RET(uchar);

    uint       getBROADCAST(void);
    void       setBROADCAST(uint);

    uchar      getSNIFER_MODE(void);
    void       setSNIFER_MODE(uchar);

    QString    getDevice_Name(void);
    void       setDevice_Name(QString);

    QList<QString>  getSwitchTable(void);
    void  setSwitchTable(QList<QString>);

    void Define_Device_Name(void);

private slots:


};

#endif // MODEMCLASS_H
