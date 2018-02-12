#ifndef CRC32_CLASS_H
#define CRC32_CLASS_H

#include <QObject>

class crc32_class : public QObject
{
    Q_OBJECT
public:
    explicit crc32_class(QObject *parent = 0);

signals:

public slots:
    unsigned long crc32_single(unsigned long pre_crc32, unsigned long value);
    unsigned long crc32(unsigned long * arr, int num);
    unsigned long crc32_from_flash(volatile unsigned int start_flash_adr, int num);
};

#endif // CRC32_CLASS_H
