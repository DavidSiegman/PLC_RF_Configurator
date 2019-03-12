#include "hands_enter_form.h"
#include "connections_form.h"

#include "OTHER_FUNCTIONS/barr_to_string.h"

Hands_Enter_Form::Hands_Enter_Form(QWidget *parent) :
    myFormAbstractClass(parent)
{
    ui = new Ui::Hands_Enter_Form;
    ui->setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    ui->SN_ENABLE->setChecked(settings.value(MANUAL_SETTINGS_SN_ENABLE).toBool());
    ui->SN_TEXT->setText(settings.value(MANUAL_SETTINGS_SN).toString());
    ui->cEnterText->setText(settings.value(MANUAL_SETTINGS_MESSAGE).toString());
    if (ui->SN_ENABLE->isChecked()){ui->SN_TEXT->setEnabled(true);}

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style);

    ui->label_2->setStyleSheet(Basic_Text_Style);
    ui->label_3->setStyleSheet(Basic_Text_Style);
    ui->CRC_OUT->setStyleSheet(Basic_Text_Style);
    ui->CRC16_2->setStyleSheet(Basic_Text_Style);

    ui->cBtnSend->setStyleSheet(Basic_Buttons_Style);
    ui->Cyclic->setStyleSheet(Basic_Buttons_Style);
    ui->ClearConsole->setStyleSheet(Basic_Buttons_Style);

    ui->Back->setStyleSheet(Buttons_Style);
    ui->btnSettings->setStyleSheet(Buttons_Style);
    ui->Next->setStyleSheet(Buttons_Style);
    ui->Next->setEnabled(false);

    ui->SN_TEXT->setStyleSheet(Background_White+Basic_Text_Style);
    ui->cEnterText->setStyleSheet(Background_White+Basic_Text_Style);

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
        //this->setFixedSize (340,560);
    }

    oCRC16                    = new CRC16_Class();

    connect(ui->ClearConsole,  SIGNAL(clicked(bool)),         ui->console, SLOT(clear()));
}

Hands_Enter_Form::~Hands_Enter_Form()
{
    delete ui;
}

void Hands_Enter_Form::on_Back_clicked(){
    this->Back_ClickHandler();
    emit Cancel(this->geometry());
    this->deleteLater();
}
void Hands_Enter_Form::ForceClose(void){
    this->ForceCloseHandler();
}
void Hands_Enter_Form::on_btnSettings_clicked(){
    emit Settings(this);
}
void Hands_Enter_Form::resizeEvent(QResizeEvent *event)
{
    resize_calculating.set_form_geometry(this->geometry());

    int text_size_1 = resize_calculating.get_text_size_1();
    int text_size_2 = resize_calculating.get_text_size_2();
    int text_size_3 = resize_calculating.get_text_size_3();
    int text_size_4 = resize_calculating.get_text_size_4();
    int text_size_5 = resize_calculating.get_text_size_5();

    QSize icons_size;
    icons_size.setWidth(resize_calculating.get_icons_size());
    icons_size.setHeight(resize_calculating.get_icons_size());

    QFont font_1 = ui->label_1->font();    font_1.setPixelSize(text_size_1);
    QFont font_2 = ui->label_2->font();    font_2.setPixelSize(text_size_2);
    QFont font_3 = ui->cBtnSend->font();   font_3.setPixelSize(text_size_3);
    //QFont font_4 = ui->label_4->font();  font_4.setPixelSize(text_size_4);
    QFont font_5 = ui->console->font();    font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_2);
    ui->label_3->setFont(font_2);

    ui->SN_TEXT->setFont(font_3);
    ui->cEnterText->setFont(font_3);

    ui->cBtnSend->setFont(font_3);
    ui->Cyclic->setFont(font_3);
    ui->ClearConsole->setFont(font_3);
    ui->console->setFont(font_5);

    QScrollBar *VerticalScrollBar = new QScrollBar(); VerticalScrollBar->setStyleSheet(ScrollBar_Style);

    ui->scrollArea->setVerticalScrollBar(VerticalScrollBar);

    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);

    emit Get_Console(ui->console);
}
void Hands_Enter_Form::on_cBtnSend_clicked()
{
    emit Get_Console(ui->console);

    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    settings.setValue(MANUAL_SETTINGS_SN_ENABLE, ui->SN_ENABLE->isChecked());
    settings.setValue(MANUAL_SETTINGS_SN, ui->SN_TEXT->text());
    settings.setValue(MANUAL_SETTINGS_MESSAGE, ui->cEnterText->text());
    settings.sync();

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

void Hands_Enter_Form::on_SN_ENABLE_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        ui->SN_TEXT->setEnabled(true);
    }
    else
    {
        ui->SN_TEXT->setEnabled(false);
    }
}

