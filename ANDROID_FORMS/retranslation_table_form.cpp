#include "retranslation_table_form.h"
#include "connections_form.h"
#include "ui_retranslation_table_form.h"
#include "STYLE/style.h"

Retranslation_Table_Form::Retranslation_Table_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Retranslation_Table_Form)
{
    ui->setupUi(this);
    this->setWindowTitle(APPLICATION_NAME);

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style);

    ui->Add_NetItem->setStyleSheet(Basic_Buttons_Style);
    ui->Del_NetItem->setStyleSheet(Basic_Buttons_Style);
    ui->Read_NetTable->setStyleSheet(Basic_Buttons_Style);
    ui->None->setStyleSheet(Basic_Buttons_Style);
    ui->Del_NetTable->setStyleSheet(Basic_Buttons_Style);
    ui->Write->setStyleSheet(Basic_Buttons_Style);
    ui->Stop->setStyleSheet(Basic_Buttons_Style);
    ui->Reset->setStyleSheet(Basic_Buttons_Style);
    ui->ClearConsole->setStyleSheet(Basic_Buttons_Style);

    ui->Back->setStyleSheet(Buttons_Style);
    ui->btnSettings->setStyleSheet(Buttons_Style);
    ui->Next->setStyleSheet(Buttons_Style);

    model = new QStandardItemModel;

    ui->NetTable->setModel(model);

    connect(ui->ClearConsole,  SIGNAL(clicked(bool)),         ui->console, SLOT(clear()));
}

Retranslation_Table_Form::~Retranslation_Table_Form()
{
    delete ui;
}

void Retranslation_Table_Form::resizeEvent(QResizeEvent *event)
{
    emit isCreated();

    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

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
    QFont font_3 = ui->Add_NetItem->font();font_3.setPixelSize(text_size_3);
    QFont font_4 = ui->Add_NetItem->font();font_4.setPixelSize(text_size_4);
    QFont font_5 = ui->console->font();    font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_2);

    ui->Add_NetItem->setFont(font_4);
    ui->Del_NetItem->setFont(font_4);
    ui->Read_NetTable->setFont(font_3);
    ui->Del_NetTable->setFont(font_3);
    ui->Write->setFont(font_3);
    ui->Stop->setFont(font_3);
    ui->Reset->setFont(font_3);
    ui->ClearConsole->setFont(font_3);

    ui->console->setFont(font_5);

    QScrollBar *VerticalScrollBar = new QScrollBar(); VerticalScrollBar->setStyleSheet(ScrollBar_Style);

    ui->scrollArea->setVerticalScrollBar(VerticalScrollBar);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
}

void Retranslation_Table_Form::on_Back_clicked()
{
    emit Get_Console(NULL);
    emit Get_Geometry(this->geometry());
    emit Cancel();
    this->deleteLater();
}

void Retranslation_Table_Form::on_Next_clicked()
{
    emit Get_Console(NULL);
    emit Get_Geometry(this->geometry());
    emit Cancel();
    this->deleteLater();
}

void Retranslation_Table_Form::on_btnSettings_clicked()
{
    emit Settings(this);
}

void Retranslation_Table_Form::on_Stop_clicked()
{
    emit Stop_Send_Data();
}


void Retranslation_Table_Form::isStopped(void)
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}

void Retranslation_Table_Form::SetProgress(uint progress)
{
    ui->progress->setValue(progress);
}

void Retranslation_Table_Form::Set_Geometry(QRect new_value)
{
    this->setGeometry(new_value);
}

void Retranslation_Table_Form::Set_In_Retranslator_Properties (RetranslatorPropertiesClass* new_data)
{
    In_Retranslator_Properties = new_data;

    Out_Retranslator_Properties->setRetranslator_Table(In_Retranslator_Properties->getRetranslator_Table());
}

void Retranslation_Table_Form::Set_Out_Retranslator_Properties (RetranslatorPropertiesClass* new_data)
{
    Out_Retranslator_Properties = new_data;
}

void Retranslation_Table_Form::on_Add_NetItem_clicked()
{

    if (Out_Retranslator_Properties->getRetranslator_Table().length() < 100) {
        bool ok;
        int i = QInputDialog::getInt(ui->scrollAreaWidgetContents, QString::fromUtf8("Введите адресс устройства"), QString::fromUtf8(""), 1, 1, 2147483647, 1, &ok);
        if (ok){
            //emit ADD_NET_TABLE_ITEM(QString::number(i));

            QString SN = QString::number(i);

            QStandardItem *item = new QStandardItem(SN);
            int model_index = Out_Retranslator_Properties->getRetranslator_Table().length();
            this->model->setItem(model_index, 0, item);
            Out_Retranslator_Properties->addNewItemToRetranslation_Table(SN);
        }
    }
}

void Retranslation_Table_Form::on_Del_NetItem_clicked()
{
    if (this->model->rowCount() > 0)
    {
        uint count = this->model->rowCount()-1;
        Out_Retranslator_Properties->delCurrentItemFromRetranslation_Table();
        //Out_Retranslator_Properties->setRetranslator_Table_Current_Index(count);
        this->model->removeRow(count);

        if (count == 0)
        {
            this->model->removeColumn(0);
        }
    }
}

void Retranslation_Table_Form::on_Read_NetTable_clicked()
{
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    emit Send_Read_Switch_Table();
}

void Retranslation_Table_Form::on_Write_clicked()
{
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    emit Send_Write_Switch_Table();
}

void Retranslation_Table_Form::isSwitch_Table(void)
{
    emit isCreated();

    Out_Retranslator_Properties->setRetranslator_Table(In_Retranslator_Properties->getRetranslator_Table());

    this->model->clear();

    QList<QString> table = Out_Retranslator_Properties->getRetranslator_Table();

    for(unsigned int i = 0; i < table.length(); i++)
    {
        QStandardItem *item = new QStandardItem(table.at(i));
        this->model->setItem(i, 0, item);
    }

    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}

void Retranslation_Table_Form::on_Del_NetTable_clicked()
{
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    emit Send_Clear_Switch_Table();
}

void Retranslation_Table_Form::isSwitch_Table_Delete(void)
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
    Out_Retranslator_Properties->clearRetranslation_Table();
    this->model->clear();
}

void Retranslation_Table_Form::on_Reset_clicked()
{
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    emit Send_RF_Reset();
}
void Retranslation_Table_Form::isRF_Reset(void)
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}

