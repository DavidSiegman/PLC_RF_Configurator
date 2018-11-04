#include "barr_to_string.h"
#include <QDebug>


QString QByteAray_To_QString(QByteArray arr)
{
    int index = 0;
    QString str1; str1.clear();
    QByteArray hex_item; hex_item.clear();
    while (index < arr.length())
    {
        hex_item.clear();
        hex_item.append(arr[index]);
        str1.append(hex_item.toHex());
        str1 += ' ';
        index++;
    }
    return str1;
}

QByteArray QString_To_QByteAray(QString str, bool crc, CRC16_Class *oCRC16)
{
    QByteArray data_to_out, data_to_write; // Текстовая переменная
    data_to_out = str.toUtf8(); // Присвоение "data" значения из EnterText

    QString str2; str2.clear();


    int index = 0, index_2 = 0;


    ushort CalcCRC16;
    uint cnt2 = 0;
    CalcCRC16 = 0xFFFF;
    while (index < data_to_out.size())
    {

        str2[index] = data_to_out[index];
        index++;
        index_2++;
        if (index_2 == 2)
        {
            bool b = false;
            uint nHex = str2.toUInt(&b,16);
            data_to_write.append((char)(nHex));
            if (crc)
            {
                CalcCRC16 = oCRC16->GetCRC16(CalcCRC16, data_to_write.at(cnt2++));
            }
            str2.clear();
            index_2 = 0;
            if (data_to_out[index] == ' ')
            {
                index++;
            }
        }
    }
    if (crc)
    {
        //ushort CRC_Calculated = oCRC16->CRC16_Generate(&data_to_write);
        QByteArray CRC_Calc;
        CRC_Calc.append((uchar)(CalcCRC16 >> 0));
        CRC_Calc.append((uchar)(CalcCRC16 >> 8));

        int index = 0;
        QString str1; str1.clear();
        QByteArray hex_item; hex_item.clear();
        QString s = "Print CRC";
        qDebug() << s;
        while (index < CRC_Calc.length())
        {
            hex_item.clear();
            hex_item.append(CRC_Calc[index]);
            str1.append(hex_item.toHex());
            str1 += ' ';
            index++;
        }
        data_to_write.append(CRC_Calc);
    }

    return data_to_write;
}
