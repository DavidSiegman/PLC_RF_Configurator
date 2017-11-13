#ifndef CRC16_CLASS_H
#define CRC16_CLASS_H

#include <QObject>

class CRC16_Class : public QObject
{
    Q_OBJECT
public:
    explicit CRC16_Class(QObject *parent = 0);

private:
    unsigned short polinomial;
signals:

public slots:
    bool Check_Byte_Stream_CRC16 (QByteArray *data_array);
    short CRC16_Generate (QByteArray *data_array);
    short GetCRC16(ushort CRC16, uchar cur_byte);
    short CRC16 (QByteArray *data_array, uint length);

    void CRC16_Add_To_ByteArray(QByteArray *data_array);
};

#endif // CRC16_CLASS_H
