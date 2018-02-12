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

private:
    Ui::MainWindow    *ui;

    QString PATCH;
    QString VERSION;
    QRegExp RegVER;

    QFile *file;
    crc32_class *CRC32;
    uint Writed_PAGES, Current_PAGE, Current_BLOCK, Current_SECTOR;
    QByteArray Writed_PAGES_CRC32;

    QByteArray DATA;
signals:

public slots:
    setPATCH(QString patch);
    QString getPATCH(void);

    setWrited_PAGES(uint new_val);
    uint getWrited_PAGES(void);

    setCurrent_PAGE(uint new_val);
    uint getCurrent_PAGE(void);

    setCurrent_BLOCK(uint new_val);
    uint getCurrent_BLOCK(void);

    setCurrent_SECTOR(uint new_val);
    uint getCurrent_SECTOR(void);

    setWrited_PAGES_CRC32(uint new_val);
    uint getWrited_PAGES_CRC32(void);
};

#endif // UPDATE_H
