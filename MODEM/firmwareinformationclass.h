#ifndef FirmwareInformationClass_H
#define FirmwareInformationClass_H

#include <QByteArray>
#include <QString>

#define PLC_MODEM         "Mилур PLC (ST750)"
#define RF_MODEM_SI4432   "Mилур RF (SI4432)"
#define RF_MODEM_SI4463   "Mилур RF (SI4463)"
#define RF_SNIFFER_SI4432 "Милур IC U/Z (SI4432)"
#define RF_SNIFFER_SI4463 "Милур IC U/Z (SI4463)"
#define RF_PLC_MODEM      "Mилур PLC/RF (ST750/SI4463)"
#define RF_PLC_SNIFFER    "Милур IC U/Z/P (SI4463)"
#define TERMINAL          "Mилур Terminal (SI4432)"

typedef struct Firmware_Information_Type
{
    QString               Device_Name;
    uchar                 Current_Firmware_Version;
    QString               String_Bootloader_Version;
    QString               String_Upgradable_Version;
    double                Bootloader_Version;
    double                Upgradable_Version;
    double                Bootloader_Version_Sniffer;
    double                Upgradable_Version_Sniffer;
    double                Bootloader_Version_Terminal;
    double                Upgradable_Version_Terminal;
    uint                  Bootloader_Size;
    uint                  Upgradable_Size;
    QByteArray            Bootloader_CRC32;
    QByteArray            Upgradable_CRC32;

} Firmware_Information;

class FirmwareInformationClass
{
public:
    FirmwareInformationClass();

    QString         getDevice_Name();


    uchar           getCurrent_Firmware_Version();
    void            setCurrent_Firmware_Version(uchar);

    QString         getString_Bootloader_Version();
    void            setString_Bootloader_Version(QString);

    QString         getString_Upgradable_Version();
    void            setString_Upgradable_Version(QString);

    double          getBootloader_Version();
    void            setBootloader_Version(double);

    double          getUpgradable_Version();
    void            setUpgradable_Version(double);

    double          getBootloader_Version_Sniffer();
    void            setBootloader_Version_Sniffer(double);

    double          getUpgradable_Version_Sniffer();
    void            setUpgradable_Version_Sniffer(double);

    double          getBootloader_Version_Terminal();
    void            setBootloader_Version_Terminal(double);

    double          getUpgradable_Version_Terminal();
    void            setUpgradable_Version_Terminal(double);

    uint            getBootloader_Size();
    void            setBootloader_Size(uint);

    uint            getUpgradable_Size();
    void            setUpgradable_Size(uint);

    QByteArray      getBootloader_CRC32();
    void            setBootloader_CRC32(QByteArray);

    QByteArray      getUpgradable_CRC32();
    void            setUpgradable_CRC32(QByteArray);

private:
    Firmware_Information Firmware_Information_Data;

    void            Define_Device_Name();
    void            setDevice_Name(QString);
};

#endif // FirmwareInformationClass_H
