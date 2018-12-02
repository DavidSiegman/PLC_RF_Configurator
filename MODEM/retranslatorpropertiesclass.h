#ifndef RETRANSLATORPROPERTIESCLASS_H
#define RETRANSLATORPROPERTIESCLASS_H
#include <QString>
#include <QList>

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

typedef struct Retranslator_Properties_Type
{

    uchar                 Retranslator_Mode;
    RF_Switch_Mask       *Retranslator_Mask;
    uint                  Retranslator_Level;
    uint                  Retranslator_Timeout;
    QList<QString>        Retranslation_Table;

    uchar                 Retranslation_Table_Current_Index;

}Retranslator_Properties;

class RetranslatorPropertiesClass
{
public:
    RetranslatorPropertiesClass();

    void            Clear_Data();

    uchar           getRetranslator_Mode();
    void            setRetranslator_Mode(uchar);

    uint            getRetranslator_Level();
    void            setRetranslator_Level(uint);

    uint            getRetranslator_Timeout();
    void            setRetranslator_Timeout(uint);

    QList<QString>  getRetranslator_Table();
    void            setRetranslator_Table(QList<QString>);

    void            addNewItemToRetranslation_Table(QString);

    void            delCurrentItemFromRetranslation_Table();

    void            clearRetranslation_Table();

    uchar           getRetranslator_Table_Current_Index();
    void            setRetranslator_Table_Current_Index(uchar);

private:
    Retranslator_Properties Retranslator_Properties_Data;
};

#endif // RETRANSLATORPROPERTIESCLASS_H
