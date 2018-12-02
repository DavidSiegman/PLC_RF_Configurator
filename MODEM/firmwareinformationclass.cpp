#include "FirmwareInformationClass.h"

FirmwareInformationClass::FirmwareInformationClass()
{
    Clear_Data();
}

void FirmwareInformationClass::Clear_Data()
{
    this->Firmware_Information_Data.Device_Name                           = "";
    this->Firmware_Information_Data.Current_Firmware_Version              = 3;
    this->Firmware_Information_Data.String_Bootloader_Version             = "";
    this->Firmware_Information_Data.String_Upgradable_Version             = "";
    this->Firmware_Information_Data.Bootloader_Version                    = 0;
    this->Firmware_Information_Data.Upgradable_Version                    = 0;
    this->Firmware_Information_Data.Bootloader_Version_Sniffer            = 0;
    this->Firmware_Information_Data.Upgradable_Version_Sniffer            = 0;
    this->Firmware_Information_Data.Bootloader_Version_Terminal           = 0;
    this->Firmware_Information_Data.Upgradable_Version_Terminal           = 0;
    this->Firmware_Information_Data.Bootloader_Size                       = 0;
    this->Firmware_Information_Data.Upgradable_Size                       = 0;
    this->Firmware_Information_Data.Bootloader_CRC32.clear();
    this->Firmware_Information_Data.Upgradable_CRC32.clear();
}

void FirmwareInformationClass::Define_Device_Name()
{
    setDevice_Name("");
    // если активная прошивка - бутлоадер
    if(getCurrent_Firmware_Version() == 0)
    {
        // если первый символ версии бутлоадера буква
        if (getBootloader_Version() == 0)
        {
            // если версия бутлоадера соответствует RF снифферу на SI4443
            if ((getBootloader_Version_Sniffer() > 0) && (getBootloader_Version_Sniffer() < 20))
            {
                setDevice_Name(RF_SNIFFER_SI4432);
            }
            // если версия бутлоадера соответствует RF-PLC снифферу
            else if(getBootloader_Version_Sniffer() >= 20)
            {
                setDevice_Name(RF_PLC_SNIFFER);
            }
            // если версия бутлоадера соответствует терминалу
            else if (getBootloader_Version_Terminal() > 0)
            {
                setDevice_Name(TERMINAL);
            }
        }
        // если версия бутлоадера соответствует PLC модему
        else if ((getBootloader_Version() > 0) && (getBootloader_Version() < 3))
        {
            setDevice_Name(PLC_MODEM);
        }
        // если версия бутлоадера соответствует RF модему на SI4432
        else if ((getBootloader_Version() >= 3) && (getBootloader_Version() < 5))
        {
            setDevice_Name(RF_MODEM_SI4432);
        }
        // если версия бутлоадера соответствует RF-PLC модему
        else if ((getBootloader_Version() >= 5) && (getBootloader_Version() < 6))
        {
            setDevice_Name(RF_PLC_MODEM);
        }
    }
    else if (getCurrent_Firmware_Version() == 1)
    {
        // если первый символ версии обновляемой прошивки буква
        if (getUpgradable_Version() == 0)
        {
            // если версия обновляемой прошивки соответствует RF снифферу на SI4443
            if ((getUpgradable_Version_Sniffer() > 0) && (getUpgradable_Version_Sniffer() < 20))
            {
                setDevice_Name(RF_SNIFFER_SI4432);
            }
            // если версия обновляемой прошивки соответствует RF-PLC снифферу
            else if(getUpgradable_Version_Sniffer() >= 20)
            {
                setDevice_Name(RF_PLC_SNIFFER);
            }
            // если версия обновляемой прошивки соответствует терминалу
            else if (getUpgradable_Version_Terminal() > 0)
            {
                setDevice_Name(TERMINAL);
            }
        }
        // если версия обновляемой прошивки соответствует PLC модему
        else if ((getUpgradable_Version() > 0) && (getUpgradable_Version() < 3))
        {
            setDevice_Name(PLC_MODEM);
        }
        // если версия обновляемой прошивки соответствует RF модему на SI4432
        else if ((getUpgradable_Version() >= 3) && (getUpgradable_Version() < 5))
        {
            setDevice_Name(RF_MODEM_SI4432);
        }
        // если версия обновляемой прошивки соответствует RF-PLC модему
        else if ((getUpgradable_Version() >= 5) && (getUpgradable_Version() < 6))
        {
            setDevice_Name(RF_PLC_MODEM);
        }
    }
}

QString    FirmwareInformationClass::getDevice_Name()
{
    Define_Device_Name();
    return Firmware_Information_Data.Device_Name;
}
void       FirmwareInformationClass::setDevice_Name( QString new_value)
{
    Firmware_Information_Data.Device_Name = new_value;
}

uchar      FirmwareInformationClass::getCurrent_Firmware_Version()
{
    return Firmware_Information_Data.Current_Firmware_Version;
}
void       FirmwareInformationClass::setCurrent_Firmware_Version(uchar new_value)
{
    Firmware_Information_Data.Current_Firmware_Version = new_value;
}

QString    FirmwareInformationClass::getString_Bootloader_Version()
{
    return Firmware_Information_Data.String_Bootloader_Version;
}
void       FirmwareInformationClass::setString_Bootloader_Version(QString new_value)
{
    Firmware_Information_Data.String_Bootloader_Version = new_value;

    setBootloader_Version(Firmware_Information_Data.String_Bootloader_Version.toDouble());

    setBootloader_Version_Sniffer(0);
    setBootloader_Version_Terminal(0);

    QString s;
    s.append(Firmware_Information_Data.String_Bootloader_Version.at(2));
    s.append(Firmware_Information_Data.String_Bootloader_Version.at(3));

    if((Firmware_Information_Data.String_Bootloader_Version.at(0) == 'R'))
    {
        setBootloader_Version_Sniffer(s.toDouble());
    }
    else if((Firmware_Information_Data.String_Bootloader_Version.at(0) == 'T'))
    {
        setBootloader_Version_Terminal(s.toDouble());
    }
}

QString    FirmwareInformationClass::getString_Upgradable_Version()
{
    return Firmware_Information_Data.String_Upgradable_Version;
}
void       FirmwareInformationClass::setString_Upgradable_Version(QString new_value)
{
    Firmware_Information_Data.String_Upgradable_Version = new_value;

    setUpgradable_Version(Firmware_Information_Data.String_Upgradable_Version.toDouble());

    setUpgradable_Version_Sniffer(0);
    setUpgradable_Version_Terminal(0);

    QString s;
    s.append(Firmware_Information_Data.String_Upgradable_Version.at(2));
    s.append(Firmware_Information_Data.String_Upgradable_Version.at(3));

    if((Firmware_Information_Data.String_Upgradable_Version.at(0) == 'R'))
    {
        setUpgradable_Version_Sniffer(s.toDouble());
    }
    else if((Firmware_Information_Data.String_Upgradable_Version.at(0) == 'T'))
    {
        setUpgradable_Version_Terminal(s.toDouble());
    }
}

double     FirmwareInformationClass::getBootloader_Version()
{
    return Firmware_Information_Data.Bootloader_Version;
}
void       FirmwareInformationClass::setBootloader_Version(double new_value)
{
    Firmware_Information_Data.Bootloader_Version = new_value;
}

double     FirmwareInformationClass::getUpgradable_Version()
{
    return Firmware_Information_Data.Upgradable_Version;
}
void       FirmwareInformationClass::setUpgradable_Version(double new_value)
{
    Firmware_Information_Data.Upgradable_Version = new_value;
}

double     FirmwareInformationClass::getBootloader_Version_Sniffer()
{
    return Firmware_Information_Data.Bootloader_Version_Sniffer;
}
void       FirmwareInformationClass::setBootloader_Version_Sniffer(double new_value)
{
    Firmware_Information_Data.Bootloader_Version_Sniffer = new_value;
}

double     FirmwareInformationClass::getUpgradable_Version_Sniffer()
{
    return Firmware_Information_Data.Upgradable_Version_Sniffer;
}
void       FirmwareInformationClass::setUpgradable_Version_Sniffer(double new_value)
{
    Firmware_Information_Data.Upgradable_Version_Sniffer = new_value;
}

double     FirmwareInformationClass::getBootloader_Version_Terminal()
{
    return Firmware_Information_Data.Bootloader_Version_Terminal;
}
void       FirmwareInformationClass::setBootloader_Version_Terminal(double new_value)
{
    Firmware_Information_Data.Bootloader_Version_Terminal = new_value;
}

double     FirmwareInformationClass::getUpgradable_Version_Terminal()
{
    return Firmware_Information_Data.Upgradable_Version_Terminal;
}
void       FirmwareInformationClass::setUpgradable_Version_Terminal(double new_value)
{
    Firmware_Information_Data.Upgradable_Version_Terminal = new_value;
}

uint       FirmwareInformationClass::getBootloader_Size()
{
    return Firmware_Information_Data.Bootloader_Size;
}
void       FirmwareInformationClass::setBootloader_Size(uint new_value)
{
    Firmware_Information_Data.Bootloader_Size = new_value;
}

uint       FirmwareInformationClass::getUpgradable_Size()
{
    return Firmware_Information_Data.Upgradable_Size;
}
void       FirmwareInformationClass::setUpgradable_Size(uint new_value)
{
    Firmware_Information_Data.Upgradable_Size = new_value;
}

QByteArray FirmwareInformationClass::getBootloader_CRC32()
{
    return Firmware_Information_Data.Bootloader_CRC32;
}
void       FirmwareInformationClass::setBootloader_CRC32(QByteArray new_value)
{
    Firmware_Information_Data.Bootloader_CRC32 = new_value;
}

QByteArray FirmwareInformationClass::getUpgradable_CRC32()
{
    return Firmware_Information_Data.Upgradable_CRC32;
}
void       FirmwareInformationClass::setUpgradable_CRC32(QByteArray new_value)
{
    Firmware_Information_Data.Upgradable_CRC32 = new_value;
}
