#include "modemclass.h"

MODEMClass::MODEMClass(Ui::MainWindow *ui, QObject *parent) : QObject(parent)
{
    curr_ver = 0; SWITCH_MODE = 0;
    SWITCH_LEVEL = 0; SWITCH_TIMEOUT = 0; RX_TIMEOUT = 0; TX_TIMEOUT = 0; LED_LOGIC = 0; CRC_CHECK_DISABLE = 0;
    RESET_DEVICE_TIMEOUT = 0; UP_LINC = 0; DIRECT_RET = 0; BROADCAST = 0; SNIFER_MODE = 0;
    boot_ver = ""; fw_ver = "";
    BOOT_VERSION = 0; FW_VERSION = 0;
    BOOT_VERSION_SNIFER = 0; FW_VERSION_SNIFER = 0;
    SwitchTable.clear();

    SWITCH_MASK             = new RF_Switch_Mask;
    SWITCH_MASK_DESTINATION = new RF_Switch_Mask;

    *(unsigned int*)(SWITCH_MASK)             = 0;
    *(unsigned int*)(SWITCH_MASK_DESTINATION) = 0;

    this->ui       = ui;

    this->model          = new QStandardItemModel();

    this->ui->NetTable       ->setModel(this->model);
    this->ui->NetTable       ->resizeRowsToContents();
    this->ui->NetTable       ->resizeColumnsToContents();

    this->current_index = 0;
}

void MODEMClass::addNewItem(QString string)
{
    this->current_index = this->model->rowCount();
    QStandardItem *item = new QStandardItem(string);
    this->model->setItem(this->current_index, 0, item);
    this->SwitchTable.append(string);
    this->current_index++;
}

void MODEMClass::delNewItem()
{
    if (this->current_index <= 100)
    {
        this->current_index--;
    }
    else
    {
        this->current_index = 0;
    }
    this->model->removeRow(this->current_index);
    this->SwitchTable.removeAt(this->current_index);
    if ((this->current_index == 0)&&(this->model->rowCount() == 0))
    {
        this->model->removeColumn(this->current_index);
    }
}

void MODEMClass::setCurrent_Index(uchar index)
{
    this->current_index = index;
}
uchar MODEMClass::getCurrent_Index()
{
    return this->current_index;
}

void MODEMClass::clearNetTable()
{
    this->current_index = 0;
    this->SwitchTable.clear();
    this->model->clear();
}

void MODEMClass::setSWITCH_LEVEL(uint lvl)
{
    this->SWITCH_LEVEL = lvl;
    *(unsigned int*)(this->SWITCH_MASK) = lvl;
    this->ui->LVL0->setValue(this->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL0);
    this->ui->LVL1->setValue(this->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL1);
    this->ui->LVL2->setValue(this->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL2);
    this->ui->LVL3->setValue(this->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL3);
    this->ui->LVL4->setValue(this->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL4);
    this->ui->LVL5->setValue(this->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL5);
    this->ui->LVL6->setValue(this->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL6);
    this->ui->LVL7->setValue(this->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL7);
    this->ui->LVL8->setValue(this->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL8);
    this->ui->LVL9->setValue(this->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL9);
}

uint MODEMClass::getSWITCH_LEVEL(void)
{
    return this->SWITCH_LEVEL;
}
