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
    this->nCRC32.clear();
    this->Writed_PAGES   = 0;
}

void UPDATE::setPATCH(QString patch)
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
        this->nCRC32.clear();
        pos = RegVER.indexIn(patch,pos) + 3;
        this->VERSION.clear();
        this->VERSION.append(this->PATCH.data() + pos,4);
        ui->new_v->setText(this->VERSION);
        ui->UPDATE_START->setEnabled(true);

        if (this->PATCH.length() != 0)
        {
            this->file = new QFile(this->PATCH);
            if(this->file->exists())
            {
                if (this->file->open(QIODevice::ReadOnly))
                {
                   DATA = file->readAll();
                   uint crc = this->CRC32->crc32((unsigned long*)(DATA.data()), DATA.length());
                   nCRC32.append((char)(crc >> 24));
                   nCRC32.append((char)(crc >> 16));
                   nCRC32.append((char)(crc >> 8));
                   nCRC32.append((char)(crc >> 0));

                   nSIZE = DATA.length();

                   ui->new_CRC->setText(QByteAray_To_QString(nCRC32).toUpper());
                   ui->new_Size->setText(QString::number(nSIZE));
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
void UPDATE::Compare_Writed_PAGES_CRC32(uint pages, uint page_size, uint in_crc32)
{
    uint crc = this->CRC32->crc32((unsigned long*)(DATA.data()), pages*page_size);
    if (crc == in_crc32)
    {
        this->Current_PAGE   = pages;
        this->Current_BLOCK  = pages*page_size/512;
        this->Current_SECTOR = 0;
        this->Writed_BYTES   = pages*page_size;
    }
    else
    {
        this->Current_PAGE   = 0;
        this->Current_BLOCK  = 0;
        this->Current_SECTOR = 0;
        this->Writed_BYTES   = 0;
    }
}

void UPDATE::getCurrent_SECTOR_DATA(QByteArray* DATA)
{
    uint length      = 0;
    uint start_index = this->Current_BLOCK*512 + this->Current_SECTOR*168;
    if (this->Current_SECTOR < 2)
    {length = 168;}
    else if (this->Current_SECTOR == 2)
    {length = 176;}
    if ((this->nSIZE - this->Writed_BYTES) < length)
    {
        length = (this->nSIZE - this->Writed_BYTES);
    }
    DATA->append((uchar)(length + 2));
    DATA->append(this->Current_BLOCK);
    DATA->append(this->Current_SECTOR);
    for(uint i = 0; i < length; i++)
    {
        DATA->append(this->DATA.at(start_index + i));
        this->Writed_BYTES++;
    }
}

void UPDATE::incCurrent_SECTOR(void)
{
    this->Current_SECTOR++;
    if (this->Current_SECTOR > 2)
    {
        this->Current_SECTOR = 0;
        this->Current_BLOCK++;
        this->Current_PAGE = this->Current_BLOCK/2;
    }
}

uint UPDATE::getSIZE(void)
{
    return this->nSIZE;
}
QByteArray UPDATE::getCRC32(void)
{
    return this->nCRC32;
}

QString UPDATE::getPATCH(void)
{
    return this->PATCH;
}

QString UPDATE::getVERSION(void)
{
    return this->VERSION;
}

uint UPDATE::getWrited_PAGES(void)
{
    return this->Writed_PAGES;
}

uint UPDATE::getWrited_BYTES(void)
{
    return this->Writed_BYTES;
}

uint UPDATE::getCurrent_PAGE(void)
{
    return this->Current_PAGE;
}

uint UPDATE::getCurrent_BLOCK(void)
{
    return this->Current_BLOCK;
}

uint UPDATE::getCurrent_SECTOR(void)
{
    return this->Current_SECTOR;
}
QByteArray* UPDATE::get_aWrited_PAGES_CRC32(void)
{
    return &this->Writed_PAGES_CRC32;
}
