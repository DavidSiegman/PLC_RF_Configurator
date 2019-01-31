#include "update.h"
#include "OTHER_FUNCTIONS/barr_to_string.h"

UPDATE::UPDATE(Ui::MainWindow *ui,QObject *parent) : QObject(parent)
{
    this->CRC32 = new crc32_class();
    this->ui = ui;

    this->Current_PAGE   = 0;
    this->Current_BLOCK  = 0;
    this->Current_SECTOR = 0;

    this->Writed_PAGES_CRC32.clear();
    this->nCRC32.clear();
    this->Writed_PAGES   = 0;
}

UPDATE::UPDATE(QObject *parent)
{
    this->CRC32 = new crc32_class();

    this->Current_PAGE   = 0;
    this->Current_BLOCK  = 0;
    this->Current_SECTOR = 0;

    this->Writed_PAGES_CRC32.clear();
    this->nCRC32.clear();
    this->Writed_PAGES   = 0;
}

void UPDATE::setDATA(QString vers,QByteArray new_DATA)
{
    this->VERSION = vers;

    DATA.clear();
    DATA = new_DATA;
    nSIZE = DATA.length();

    this->nCRC32.clear();
    uint crc = this->CRC32->crc32((unsigned long*)(DATA.data()), DATA.length());
    nCRC32.append((char)(crc >> 24));
    nCRC32.append((char)(crc >> 16));
    nCRC32.append((char)(crc >> 8));
    nCRC32.append((char)(crc >> 0));
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
    this->Writed_BYTES = start_index;
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
