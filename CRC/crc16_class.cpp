#include "CRC/crc16_class.h"

CRC16_Class::CRC16_Class(QObject *parent) : QObject(parent)
{
    polinomial = 0xA001;
}
bool CRC16_Class::Check_Byte_Stream_CRC16 (QByteArray *data_array)
{
    bool result = false;

    ushort CRC_Calculated = 0;

    if (data_array->length() >= 2)
    {
        CRC_Calculated = CRC16 (data_array, (data_array->length()-2));

        QByteArray p_char;
        p_char.append((uchar)(CRC_Calculated >> 0));
        p_char.append((uchar)(CRC_Calculated >> 8));
        if ((data_array->at(data_array->length() - 2) == p_char.at(0)) && (data_array->at(data_array->length() - 1) == p_char.at(1)))
        {
            result = true;
        }
    }
    return result;
}
short CRC16_Class::CRC16_Generate (QByteArray *data_array)
{
    return CRC16(data_array,data_array->length());
}
short CRC16_Class::GetCRC16(ushort CRC16, uchar cur_byte)
{
   uchar uIndex = 8;
   ushort Carry;
   CRC16 = CRC16 ^ cur_byte;
   do
   {
      Carry = CRC16 & 0x0001;
      CRC16 = CRC16 >> 1;
      CRC16 &= 0x7fff;
      if (Carry == 1)
      {
         CRC16 = CRC16 ^ polinomial;
      }
    }
    while (--uIndex);            // pass through message buffer
    return CRC16;
}
short CRC16_Class::CRC16 (QByteArray *data_array, uint length)
{
    ushort CalcCRC16;
    uint cnt1,cnt2;
    CalcCRC16 = 0xFFFF;
    cnt1 = length;
    cnt2 = 0;
    while ( cnt2 < cnt1)
    {
       CalcCRC16 = GetCRC16(CalcCRC16, data_array->at(cnt2++));
    }
    return CalcCRC16;
}
void CRC16_Class::CRC16_Add_To_ByteArray(QByteArray *data_array)
{
    ushort CRC_Calculated = CRC16_Generate(data_array);
    QByteArray CRC_Calc_2;
    CRC_Calc_2.append((uchar)(CRC_Calculated >> 0));
    CRC_Calc_2.append((uchar)(CRC_Calculated >> 8));

    data_array->append(CRC_Calc_2);
}
