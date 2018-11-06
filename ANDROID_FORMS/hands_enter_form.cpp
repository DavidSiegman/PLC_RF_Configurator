#include "hands_enter_form.h"
#include "ui_hands_enter_form.h"
#include "OTHER_FUNCTIONS/barr_to_string.h"

Hands_Enter_Form::Hands_Enter_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hands_Enter_Form)
{
    ui->setupUi(this);

    SysInfo              = new QSysInfo;
    QString product_name = SysInfo->prettyProductName();

    RegSystemName        = QRegExp("[A-Za-z]+");
    RegSystemName.indexIn(product_name,0);
    if (RegSystemName.cap(0).compare("Android") == 0)
    {
        setWindowState(Qt::WindowMaximized);
    }
    else if (RegSystemName.cap(0).compare("Windows") == 0)
    {
        this->setWindowModality(Qt::WindowModal);
        this->setFixedSize (340,560);
    }

    oCRC16                    = new CRC16_Class();
}

Hands_Enter_Form::~Hands_Enter_Form()
{
    delete ui;
}

void Hands_Enter_Form::on_Back_clicked()
{
    emit Cancel();
    this->deleteLater();
}

void Hands_Enter_Form::on_cBtnSend_clicked()
{
    emit Get_Console(ui->console);

    QByteArray data_to_write; // Текстовая переменная
    int sn = 0;

    QString str2;
    str2.clear();

    if (ui->SN_ENABLE->isChecked())
    {
        sn = ui->SN_TEXT->text().toInt();
        data_to_write.append((char)(sn >> 0));
        data_to_write.append((char)(sn >> 8));
        data_to_write.append((char)(sn >> 16));
        data_to_write.append((char)(sn >> 24));
    }

    data_to_write.append(QString_To_QByteAray(ui->cEnterText->text(), ui->CRC_OUT->isChecked(),oCRC16));

    if (ui->CRC_OUT->isChecked())
    {
        QByteArray CRC_Calc;
        CRC_Calc.append(data_to_write.at(data_to_write.length()-2));
        CRC_Calc.append(data_to_write.at(data_to_write.length()-1));
        ui->CRC_OUT->setText(QByteAray_To_QString(CRC_Calc).toUpper());
    }
    else
    {
        ui->CRC_OUT->setText("CRC16");
    }

    if (ui->SN_ENABLE->isChecked())
    {
        ushort CRC_Calculated = oCRC16->CRC16_Generate(&data_to_write);
        QByteArray CRC_Calc_2;
        CRC_Calc_2.append((uchar)(CRC_Calculated >> 0));
        CRC_Calc_2.append((uchar)(CRC_Calculated >> 8));

        ui->CRC16_2->setText(QByteAray_To_QString(CRC_Calc_2).toUpper());

        data_to_write.append(CRC_Calc_2);
    }
    else
    {
        ui->CRC16_2->setText("CRC16");
    }
    if (data_to_write.length() > 0)
    {
        if (ui->Cyclic->isChecked())
        {
            emit Send_Data(data_to_write,MANUAL_CYCLIC_SEND_CONTROL);
            //DataLogic->SEND_DATA(data_to_write,MANUAL_CYCLIC_SEND_CONTROL);
        }
        else
        {
            emit Send_Data(data_to_write,MANUAL_SEND_CONTROL);
            //DataLogic->SEND_DATA(data_to_write,MANUAL_SEND_CONTROL);
        }
    }
}

void Hands_Enter_Form::on_pushButton_clicked()
{
    ui->console->clear();
}
