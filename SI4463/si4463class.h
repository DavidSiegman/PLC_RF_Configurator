#ifndef SI4463CLASS_H
#define SI4463CLASS_H

#include <QObject>
#include <SI4463/si4463_propertys_type.h>

class SI4463Class : public QObject
{
    Q_OBJECT
public:
    explicit SI4463Class(QObject *parent = 0);

private:
    SI4463_PROPERTYS_structur    SI4463_PROPERTYS;
    SI4463_PART_INFO_structur    SI4463_PART_INFO;
    SI4463_INTERUPTS_structur    SI4463_INTERUPTS;
    SI4463_GPIO_PIN_CFG_structur SI4463_GPIO_PIN_CFG;
signals:

public slots:
    SI4463_PROPERTYS_structur*     aSI4463_PROPERTYS(void);
    SI4463_PART_INFO_structur*     aSI4463_PART_INFO(void);
    SI4463_INTERUPTS_structur*     aSI4463_INTERUPTS(void);
    SI4463_GPIO_PIN_CFG_structur*  aSI4463_GPIO_PIN_CFG(void);

    uchar* SI4463_Get_Group_Adress_From_RAM(uchar GROUP, uchar START_PROP);

    uchar* SI4463_PROPS_GROUP_00();
    uchar* SI4463_PROPS_GROUP_01();
    uchar* SI4463_PROPS_GROUP_02();
    uchar* SI4463_PROPS_GROUP_10();
    uchar* SI4463_PROPS_GROUP_11();
    uchar* SI4463_PROPS_GROUP_12();
    uchar* SI4463_PROPS_GROUP_20();
    uchar* SI4463_PROPS_GROUP_21();
    uchar* SI4463_PROPS_GROUP_22();
    uchar* SI4463_PROPS_GROUP_23();
    uchar* SI4463_PROPS_GROUP_30();
    uchar* SI4463_PROPS_GROUP_40();
    uchar* SI4463_PROPS_GROUP_50();
};


#endif // SI4463CLASS_H
