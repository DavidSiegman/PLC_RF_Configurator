#include "SI4463/si4463class.h"

SI4463Class::SI4463Class(QObject *parent) : QObject(parent)
{

}
SI4463_PROPERTYS_structur* SI4463Class::aSI4463_PROPERTYS(void)
{
    return &SI4463_PROPERTYS;
}
SI4463_PART_INFO_structur*        SI4463Class::aSI4463_PART_INFO(void)
{
    return &SI4463_PART_INFO;
}
SI4463_INTERUPTS_structur*        SI4463Class::aSI4463_INTERUPTS(void)
{
    return &SI4463_INTERUPTS;
}
SI4463_GPIO_PIN_CFG_structur*     SI4463Class::aSI4463_GPIO_PIN_CFG(void)
{
    return &SI4463_GPIO_PIN_CFG;
}


uchar* SI4463Class::SI4463_Get_Group_Adress_From_RAM(uchar GROUP, uchar START_PROP)
{
    uchar *group_adress = 0;
    switch (GROUP)
    {
        case 0x00: // GLOBAL (0x00)
        {
            group_adress = (this->SI4463_PROPS_GROUP_00() + START_PROP);
            break;
        }
        case 0x01: // INT_CTL (0x01)
        {
            group_adress = (this->SI4463_PROPS_GROUP_01() + START_PROP);
            break;
        }
        case 0x02: // FRR_CTL (0x02)
        {
            group_adress = (this->SI4463_PROPS_GROUP_02() + START_PROP);
            break;
        }
        case 0x10: // PREAMBLE (0x10)
        {
            group_adress = (this->SI4463_PROPS_GROUP_10() + START_PROP);
            break;
        }
        case 0x11: // SYNC (0x11)
        {
            group_adress = (this->SI4463_PROPS_GROUP_11() + START_PROP);
            break;
        }
        case 0x12: // PKT (0x12)
        {
            group_adress = (this->SI4463_PROPS_GROUP_12() + START_PROP);
            break;
        }
        case 0x20: // MODEM (0x20)
        {
            group_adress = (this->SI4463_PROPS_GROUP_20() + START_PROP);
            break;
        }
        case 0x21: // MODEM_CHFLT (0x21)
        {
            group_adress = (this->SI4463_PROPS_GROUP_21() + START_PROP);
            break;
        }
        case 0x22: // PA (0x22)
        {
            group_adress = (this->SI4463_PROPS_GROUP_22() + START_PROP);
            break;
        }
        case 0x23: // SYNTH (0x23)
        {
            group_adress = (this->SI4463_PROPS_GROUP_23() + START_PROP);
            break;
        }
        case 0x30: // MATCH (0x30)
        {
            group_adress = (this->SI4463_PROPS_GROUP_30() + START_PROP);
            break;
        }
        case 0x40: // FREQ_CONTROL (0x40)
        {
            group_adress = (this->SI4463_PROPS_GROUP_40() + START_PROP);
            break;
        }
        case 0x50: // RX_HOP (0x50)
        {
            group_adress = (this->SI4463_PROPS_GROUP_50() + START_PROP);
            break;
        }
    }
    return (uchar *)(group_adress);
}

uchar* SI4463Class::SI4463_PROPS_GROUP_00()
{
    return (uchar *)(aSI4463_PROPERTYS()->Field.GROUP_00.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_01()
{
    return (uchar *)(aSI4463_PROPERTYS()->Field.GROUP_01.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_02()
{
    return (uchar *)(aSI4463_PROPERTYS()->Field.GROUP_02.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_10()
{
    return (uchar *)(aSI4463_PROPERTYS()->Field.GROUP_10.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_11()
{
    return (uchar *)(aSI4463_PROPERTYS()->Field.GROUP_11.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_12()
{
    return (uchar *)(aSI4463_PROPERTYS()->Field.GROUP_12.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_20()
{
    return (uchar *)(aSI4463_PROPERTYS()->Field.GROUP_20.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_21()
{
    return (uchar *)(aSI4463_PROPERTYS()->Field.GROUP_21.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_22()
{
    return (uchar *)(aSI4463_PROPERTYS()->Field.GROUP_22.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_23()
{
    return (uchar *)(aSI4463_PROPERTYS()->Field.GROUP_23.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_30()
{
    return (uchar *)(aSI4463_PROPERTYS()->Field.GROUP_30.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_40()
{
    return (uchar *)(aSI4463_PROPERTYS()->Field.GROUP_40.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_50()
{
    return (uchar *)(aSI4463_PROPERTYS()->Field.GROUP_50.Bytes);
}

