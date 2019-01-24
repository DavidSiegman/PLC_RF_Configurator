#ifndef SNIFFERPROPERTIESCLASS_H
#define SNIFFERPROPERTIESCLASS_H

#include "retranslatorpropertiesclass.h"

typedef struct Sniffer_Properties_Type
{
    uchar                 Sniffer_Mode;
    uchar                 UpLink_Value;
    uchar                 CRC_Check_Disable;
    uchar                 Broadcasting;
    RF_Switch_Mask       *Sniffer_Mask_Destination;
    uint                  Sniffer_Level_Destination;
    uchar                 Direct_Transfer;

}Sniffer_Properties;

class SnifferPropertiesClass
{
public:
    SnifferPropertiesClass();

    void            Clear_Data();

    uchar           getSniffer_Mode();
    void            setSniffer_Mode(uchar);

    uchar           getUpLink_Value();
    void            setUpLink_Value(uchar);

    uchar           getCRC_Check_Disable();
    void            setCRC_Check_Disable(uchar);

    uchar           getBroadcasting();
    void            setBroadcasting(uchar);

    uint            getSniffer_Level_Destination();
    void            setSniffer_Level_Destination(uint);

    uchar           getDirect_Transfer();
    void            setDirect_Transfer(uchar);

private:
    Sniffer_Properties Sniffer_Properties_Data;
};

#endif // SNIFFERPROPERTIESCLASS_H
