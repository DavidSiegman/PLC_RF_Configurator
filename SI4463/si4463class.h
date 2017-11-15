#ifndef SI4463CLASS_H
#define SI4463CLASS_H

#include <QObject>
#include <QStandardItemModel>
#include <SI4463/si4463_propertys_type.h>
#include <SI4463/si4463_propertys_tablemodel.h>

class SI4463Class : public QObject
{
    Q_OBJECT
public:
    explicit SI4463Class(QObject *parent = 0);
    QList<QString> SI4463_PROPERTYS_NAME;
    QStandardItemModel *model;

    void aSI4463_SET_CurrentPROPERTYS(uchar GROUP, uchar START_PROP, uint PROP_COUNTER, uchar PROP_DATA);

private:
    SI4463_PROPERTYS_structur    SI4463_PROPERTYS;
    SI4463_PART_INFO_structur    SI4463_PART_INFO;
    SI4463_INTERUPTS_structur    SI4463_INTERUPTS;
    SI4463_GPIO_PIN_CFG_structur SI4463_GPIO_PIN_CFG;

    QStandardItem *item;

    uint SI4463_PROPERTYS_BytesNumber;

    uint GROUP_00_BytesNumber;
    uint GROUP_01_BytesNumber;
    uint GROUP_02_BytesNumber;
    uint GROUP_10_BytesNumber;
    uint GROUP_11_BytesNumber;
    uint GROUP_12_BytesNumber;
    uint GROUP_20_BytesNumber;
    uint GROUP_21_BytesNumber;
    uint GROUP_22_BytesNumber;
    uint GROUP_23_BytesNumber;
    uint GROUP_30_BytesNumber;
    uint GROUP_40_BytesNumber;
    uint GROUP_50_BytesNumber;

signals:

public slots:
    SI4463_PROPERTYS_structur*     aSI4463_PROPERTYS(void);
    SI4463_PART_INFO_structur*     aSI4463_PART_INFO(void);
    SI4463_INTERUPTS_structur*     aSI4463_INTERUPTS(void);
    SI4463_GPIO_PIN_CFG_structur*  aSI4463_GPIO_PIN_CFG(void);

    uchar* SI4463_Get_Group_Adress_From_RAM(uchar GROUP, uchar START_PROP);

    uchar* SI4463_PROPS_GROUP_00(void);
    uchar* SI4463_PROPS_GROUP_01(void);
    uchar* SI4463_PROPS_GROUP_02(void);
    uchar* SI4463_PROPS_GROUP_10(void);
    uchar* SI4463_PROPS_GROUP_11(void);
    uchar* SI4463_PROPS_GROUP_12(void);
    uchar* SI4463_PROPS_GROUP_20(void);
    uchar* SI4463_PROPS_GROUP_21(void);
    uchar* SI4463_PROPS_GROUP_22(void);
    uchar* SI4463_PROPS_GROUP_23(void);
    uchar* SI4463_PROPS_GROUP_30(void);
    uchar* SI4463_PROPS_GROUP_40(void);
    uchar* SI4463_PROPS_GROUP_50(void);
};

#endif // SI4463CLASS_H
