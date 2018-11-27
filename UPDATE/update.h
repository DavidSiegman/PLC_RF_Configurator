#ifndef UPDATE_H
#define UPDATE_H

#include <QObject>
#include "ui_mainwindow.h"
#include "CRC/crc32_class.h"
class UPDATE : public QObject
{
    Q_OBJECT
public:
    explicit UPDATE(Ui::MainWindow *ui,QObject *parent = 0);
    explicit UPDATE(QObject *parent = 0);

private:
    Ui::MainWindow    *ui;

    QString VERSION;

    crc32_class *CRC32;
    uint Writed_PAGES, Current_PAGE, Current_BLOCK, Current_SECTOR, nSIZE, Writed_BYTES;
    QByteArray Writed_PAGES_CRC32, nCRC32;

    QByteArray DATA;
signals:

public slots:
    void setDATA(QString,QByteArray);

    QString getVERSION(void);

    uint getWrited_PAGES(void);

    uint getWrited_BYTES(void);

    uint getCurrent_PAGE(void);

    uint getCurrent_BLOCK(void);

    uint getCurrent_SECTOR(void);

    void getCurrent_SECTOR_DATA(QByteArray* DATA);

    void incCurrent_SECTOR(void);

    QByteArray* get_aWrited_PAGES_CRC32(void);

    uint getSIZE(void);

    QByteArray getCRC32(void);

    void Compare_Writed_PAGES_CRC32(uint pages, uint page_size, uint in_crc32);
};

#endif // UPDATE_H
