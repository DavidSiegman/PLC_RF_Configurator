#ifndef BARR_TO_STRING
#define BARR_TO_STRING

#include "CRC/crc16_class.h"

QString    QByteAray_To_QString(QByteArray arr);

QByteArray QString_To_QByteAray(QString str, bool crc, CRC16_Class *oCRC16);

#endif // BARR_TO_STRING

