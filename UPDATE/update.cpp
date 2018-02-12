#include "update.h"
#include "barr_to_string.h"

UPDATE::UPDATE(Ui::MainWindow *ui,QObject *parent) : QObject(parent)
{
    this->CRC32 = new crc32_class();
    this->file = NULL;
    this->PATCH.clear();
    this->ui = ui;
    this->RegVER      = QRegExp("ver");

    this->Current_PAGE   = 0;
    this->Current_BLOCK  = 0;
    this->Current_SECTOR = 0;

    this->Writed_PAGES_CRC32.clear();
    this->Writed_PAGES   = 0;
}

UPDATE::setPATCH(QString patch)
{
    if (this->file != NULL)
    {
        if (this->file->isOpen())
        {
            this->file->close();
        }
    }
    int pos = 0;
    this->PATCH   = patch;

    if (this->RegVER.indexIn(patch,0) != -1)
    {
        DATA.clear();
        pos = RegVER.indexIn(patch,pos) + 3;
        this->VERSION.clear();
        this->VERSION.append(this->PATCH.data() + pos,4);
        ui->new_v->setText(this->VERSION);
        ui->UPDATE_START->setEnabled(true);

        if (this->PATCH.length() != NULL)
        {
            this->file = new QFile(this->PATCH);
            if(this->file->exists())
            {
                if (this->file->open(QIODevice::ReadOnly))
                {
                   DATA = file->readAll();
                   uint crc = this->CRC32->crc32((unsigned long*)(DATA.data()), DATA.length());
                   QByteArray CRC_32;
                   CRC_32.append((char)(crc >> 24));
                   CRC_32.append((char)(crc >> 16));
                   CRC_32.append((char)(crc >> 8));
                   CRC_32.append((char)(crc >> 0));
                   ui->new_CRC->setText(QByteAray_To_QString(CRC_32));
                   ui->new_Size->setText(QString::number(DATA.length()));
                }
            }
        }
    }
    else
    {
        ui->new_v->setText("NAN");
        ui->UPDATE_START->setEnabled(false);
    }
}

QString UPDATE::getPATCH(void)
{
    return this->PATCH;
}

UPDATE::setWrited_PAGES(uint new_val)
{
    this->Writed_PAGES = new_val;
}
uint UPDATE::getWrited_PAGES(void)
{
    return this->Writed_PAGES;
}
UPDATE::setCurrent_PAGE(uint new_val)
{
    this->Current_PAGE = new_val;
}
uint UPDATE::getCurrent_PAGE(void)
{
    return this->Current_PAGE;
}
UPDATE::setCurrent_BLOCK(uint new_val)
{
    this->Current_BLOCK = new_val;
}
uint UPDATE::getCurrent_BLOCK(void)
{
    return this->Current_BLOCK;
}
UPDATE::setCurrent_SECTOR(uint new_val)
{
    this->Current_SECTOR = new_val;
}
uint UPDATE::getCurrent_SECTOR(void)
{
    return this->Current_SECTOR;
}
UPDATE::setWrited_PAGES_CRC32(uint new_val)
{
    this->Writed_PAGES_CRC32 = new_val;
}
uint UPDATE::getWrited_PAGES_CRC32(void)
{
    return this->Writed_PAGES_CRC32;
}
