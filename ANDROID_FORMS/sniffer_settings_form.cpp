#include "sniffer_settings_form.h"
#include "connections_form.h"
#include "ui_sniffer_settings_form.h"

#include "STYLE/style.h"

Sniffer_Settings_Form::Sniffer_Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sniffer_Settings_Form)
{
    ui->setupUi(this);
    this->setWindowTitle(APPLICATION_NAME);

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style);

    ui->SetDestinationMASK->setStyleSheet(Basic_Buttons_Style);
    ui->SetNetLevel->setStyleSheet(Basic_Buttons_Style);
    ui->SetDeviceMonitorSN->setStyleSheet(Basic_Buttons_Style);
    ui->Write->setStyleSheet(Basic_Buttons_Style);
    ui->Stop->setStyleSheet(Basic_Buttons_Style);
    ui->Reset->setStyleSheet(Basic_Buttons_Style);
    ui->ClearConsole->setStyleSheet(Basic_Buttons_Style);

    ui->Back->setStyleSheet(Buttons_Style);
    ui->btnSettings->setStyleSheet(Buttons_Style);
    ui->Next->setStyleSheet(Buttons_Style);

    ui->Sniffer_Mode->setStyleSheet(Background_White);
    ui->LVL0->setStyleSheet(Background_White);
    ui->LVL1->setStyleSheet(Background_White);
    ui->LVL2->setStyleSheet(Background_White);
    ui->LVL3->setStyleSheet(Background_White);
    ui->LVL4->setStyleSheet(Background_White);
    ui->LVL5->setStyleSheet(Background_White);
    ui->LVL6->setStyleSheet(Background_White);
    ui->LVL7->setStyleSheet(Background_White);
    ui->LVL8->setStyleSheet(Background_White);
    ui->LVL9->setStyleSheet(Background_White);

    ui->NetLevel->setStyleSheet(Background_White+Basic_Text_Style);
    ui->DeviceMonitorSN->setStyleSheet(Background_White+Basic_Text_Style);


    connect(ui->ClearConsole,  SIGNAL(clicked(bool)),         ui->console, SLOT(clear()));
}

Sniffer_Settings_Form::~Sniffer_Settings_Form()
{
    delete ui;
}

void Sniffer_Settings_Form::resizeEvent(QResizeEvent *event)
{
    emit isCreated();
    this->resizing_going = 1;

    resize_calculating.set_form_geometry(this->geometry());

    int text_size_1 = resize_calculating.get_text_size_1();
    int text_size_2 = resize_calculating.get_text_size_2();
    int text_size_3 = resize_calculating.get_text_size_3();
    int text_size_4 = resize_calculating.get_text_size_4();
    int text_size_5 = resize_calculating.get_text_size_5();

    QSize icons_size;
    icons_size.setWidth(resize_calculating.get_icons_size());
    icons_size.setHeight(resize_calculating.get_icons_size());

    QFont font_1 = ui->label_1->font();     font_1.setPixelSize(text_size_1);
    QFont font_2 = ui->label_2->font();     font_2.setPixelSize(text_size_4);
    QFont font_3 = ui->Write->font();       font_3.setPixelSize(text_size_3);
    QFont font_4 = ui->Up_Link->font();     font_4.setPixelSize(text_size_4);
    QFont font_5 = ui->console->font();     font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_2);

    ui->Sniffer_Mode->setFont(font_4);
    int current_index = ui->Sniffer_Mode->currentIndex();
    ui->Sniffer_Mode->clear();
    ui->Sniffer_Mode->addItem("Normal");
    ui->Sniffer_Mode->addItem("Sniffer");
    ui->Sniffer_Mode->addItem("Sniffer + Preamble");
    ui->Sniffer_Mode->setCurrentIndex(current_index);

    ui->Up_Link->setFont(font_4);
    ui->Disable_CRC->setFont(font_4);
    ui->Broadcasting->setFont(font_4);

    ui->LVL0->setFont(font_4);
    ui->LVL1->setFont(font_4);
    ui->LVL2->setFont(font_4);
    ui->LVL3->setFont(font_4);
    ui->LVL4->setFont(font_4);
    ui->LVL5->setFont(font_4);
    ui->LVL6->setFont(font_4);
    ui->LVL7->setFont(font_4);
    ui->LVL8->setFont(font_4);
    ui->LVL9->setFont(font_4);

    ui->SetDestinationMASK->setFont(font_3);
    ui->SetNetLevel->setFont(font_3);
    ui->SetDeviceMonitorSN->setFont(font_3);
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

    this->resizing_going = 0;
}

void Sniffer_Settings_Form::on_Back_clicked()
{
    emit Cancel(this->geometry());
}

void Sniffer_Settings_Form::on_Next_clicked()
{
    emit Next(this->geometry());
}

void Sniffer_Settings_Form::on_btnSettings_clicked()
{
    emit Settings(this);
}

void Sniffer_Settings_Form::SetProgress(uint progress)
{
    ui->progress->setValue(progress);
}

void Sniffer_Settings_Form::Set_Geometry(QRect new_value)
{
    this->setGeometry(new_value);
}

void Sniffer_Settings_Form::Set_Out_Sniffer_Properties(SnifferPropertiesClass* new_data)
{
    Out_Sniffer_Properties = new_data;
}

void Sniffer_Settings_Form::Set_In_Sniffer_Properties(SnifferPropertiesClass* new_data)
{
    In_Sniffer_Properties  = new_data;

    Out_Sniffer_Properties->setSniffer_Mode(In_Sniffer_Properties->getSniffer_Mode());
    Out_Sniffer_Properties->setUpLink_Value(In_Sniffer_Properties->getUpLink_Value());
    Out_Sniffer_Properties->setCRC_Check_Disable(In_Sniffer_Properties->getCRC_Check_Disable());
    Out_Sniffer_Properties->setBroadcasting(In_Sniffer_Properties->getBroadcasting());
    Out_Sniffer_Properties->setSniffer_Level_Destination(In_Sniffer_Properties->getSniffer_Level_Destination());
    Out_Sniffer_Properties->setDirect_Transfer(In_Sniffer_Properties->getDirect_Transfer());

    SetMaskDestinationToUI(Get_Mask_Destination());

}
void Sniffer_Settings_Form::Set_Out_Retranslator_Properties (RetranslatorPropertiesClass* new_data)
{
    Out_Retranslator_Properties = new_data;
}
void Sniffer_Settings_Form::Set_In_Retranslator_Properties (RetranslatorPropertiesClass* new_data)
{
    In_Retranslator_Properties = new_data;

    Out_Retranslator_Properties->setRetranslator_Level(In_Retranslator_Properties->getRetranslator_Level());
    Out_Retranslator_Properties->setRetranslator_Mode(In_Retranslator_Properties->getRetranslator_Mode());
    Out_Retranslator_Properties->setRetranslator_Table(In_Retranslator_Properties->getRetranslator_Table());
    Out_Retranslator_Properties->setRetranslator_Table_Current_Index(In_Retranslator_Properties->getRetranslator_Table_Current_Index());
    Out_Retranslator_Properties->setRetranslator_Timeout(In_Retranslator_Properties->getRetranslator_Timeout());

    if (Out_Retranslator_Properties->getRetranslator_Table().length() > 0)
    {
        SetTableItemToUI(Out_Retranslator_Properties->getRetranslator_Table().at(0));
    }
    else
    {
        SetTableItemToUI("");
    }
}

void Sniffer_Settings_Form::Set_SnifferMode(uchar new_value)
{
    Out_Sniffer_Properties->setSniffer_Mode(new_value);
}
void Sniffer_Settings_Form::Set_UpLink(uchar new_value)
{
    Out_Sniffer_Properties->setUpLink_Value(new_value);
}
void Sniffer_Settings_Form::Set_CRCDisable(uchar new_value)
{
    Out_Sniffer_Properties->setCRC_Check_Disable(new_value);
}
void Sniffer_Settings_Form::Set_Broadcasting(uchar new_value)
{
    Out_Sniffer_Properties->setBroadcasting(new_value);
}
void Sniffer_Settings_Form::Set_Mask_Destination(uint new_value)
{
    Out_Sniffer_Properties->setSniffer_Level_Destination(new_value);
}
uint  Sniffer_Settings_Form::Get_Mask_Destination(void)
{
    return Out_Sniffer_Properties->getSniffer_Level_Destination();
}

void Sniffer_Settings_Form::on_Sniffer_Mode_currentIndexChanged(int index)
{
    if ((index >= 0)&&(index < 3)&&(this->resizing_going == 0))
    {
        emit Get_Console(ui->console);
        emit Set_SnifferMode((uchar)(index));

        ui->Stop->setEnabled(true);
        ui->SettingsWidget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit Send_Sniffer_Mode();
    }
}

void Sniffer_Settings_Form::on_Up_Link_stateChanged(int arg1)
{
    emit Get_Console(ui->console);
    if (arg1 == 0)
    {
        Set_UpLink(0);

    }
    else
    {
        Set_UpLink(1);
    }

    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    emit Send_UpLink_Mode();
}

void Sniffer_Settings_Form::on_Disable_CRC_stateChanged(int arg1)
{
    emit Get_Console(ui->console);
    if (arg1 == 0)
    {
        Set_CRCDisable(0);
    }
    else
    {
        Set_CRCDisable(1);
    }

    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    emit Send_CRC_Disable_Mode();
}

void Sniffer_Settings_Form::on_Broadcasting_stateChanged(int arg1)
{
    emit Get_Console(ui->console);
    if (arg1 == 0)
    {
        Set_Broadcasting(0);
    }
    else
    {
        Set_Broadcasting(1);
    }

    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    emit Send_Broadcasting_Mode();
}

void Sniffer_Settings_Form::on_Reset_clicked()
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

void Sniffer_Settings_Form::on_SetDestinationMASK_clicked()
{
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    emit Send_Mask_Destination();
}

void Sniffer_Settings_Form::on_SetNetLevel_clicked()
{
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    emit Set_Switch_Prop();
}

void Sniffer_Settings_Form::on_SetDeviceMonitorSN_clicked()
{
    emit Get_Console(ui->console);

    Out_Retranslator_Properties->clearRetranslation_Table();

    int numb = ui->DeviceMonitorSN->text().toInt();
    if (numb > 0)
    {
        Out_Retranslator_Properties->addNewItemToRetranslation_Table(ui->DeviceMonitorSN->text());

        ui->Stop->setEnabled(true);
        ui->SettingsWidget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit Send_Write_Switch_Table();
    }
    else
    {
        ui->Stop->setEnabled(true);
        ui->SettingsWidget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit Send_Clear_Switch_Table();
    }
}

void Sniffer_Settings_Form::SetMaskDestinationToUI(uint mask)
{
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = mask;

    ui->LVL0->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL0);
    ui->LVL1->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL1);
    ui->LVL2->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL2);
    ui->LVL3->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL3);
    ui->LVL4->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL4);
    ui->LVL5->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL5);
    ui->LVL6->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL6);
    ui->LVL7->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL7);
    ui->LVL8->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL8);
    ui->LVL9->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL9);
}

void Sniffer_Settings_Form::SetTableItemToUI(QString item)
{
    ui->DeviceMonitorSN->setText(item);
}

void Sniffer_Settings_Form::isStopped(void)
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}

void Sniffer_Settings_Form::isSnifferMode(void)
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Sniffer_Settings_Form::isUpLink_Mode(void)
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Sniffer_Settings_Form::isCRC_Disable_Mode(void)
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Sniffer_Settings_Form::isBroadcasting_Mode(void)
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Sniffer_Settings_Form::isMask_Destination(void)
{

    Out_Sniffer_Properties->setSniffer_Level_Destination(In_Sniffer_Properties->getSniffer_Level_Destination());
    SetMaskDestinationToUI(Get_Mask_Destination());

    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Sniffer_Settings_Form::isSwitch_Prop(void)
{

}
void Sniffer_Settings_Form::isSwitch_Table(void)
{
    Out_Retranslator_Properties->setRetranslator_Table(In_Retranslator_Properties->getRetranslator_Table());
    Out_Retranslator_Properties->setRetranslator_Table_Current_Index(In_Retranslator_Properties->getRetranslator_Table_Current_Index());

    if (Out_Retranslator_Properties->getRetranslator_Table().length() > 0)
    {
        SetTableItemToUI(Out_Retranslator_Properties->getRetranslator_Table().at(0));
    }
    else
    {
        SetTableItemToUI("");
    }

    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Sniffer_Settings_Form::isSwitch_Table_Delete(void)
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Sniffer_Settings_Form::isRF_Reset(void)
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}

void Sniffer_Settings_Form::on_LVL0_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL0 = arg1;
    if (arg1 > 0)
    {
        ui->LVL1->setEnabled(true);
    }
    else
    {
        ui->LVL1->setEnabled(false); ui->LVL1->setValue(0);
        ui->LVL2->setEnabled(false); ui->LVL2->setValue(0);
        ui->LVL3->setEnabled(false); ui->LVL3->setValue(0);
        ui->LVL4->setEnabled(false); ui->LVL4->setValue(0);
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL1 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL4 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL2 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL3 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void Sniffer_Settings_Form::on_LVL1_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL1 = arg1;

    if (arg1 > 0)
    {
        ui->LVL2->setEnabled(true);
    }
    else
    {
        ui->LVL2->setEnabled(false); ui->LVL2->setValue(0);
        ui->LVL3->setEnabled(false); ui->LVL3->setValue(0);
        ui->LVL4->setEnabled(false); ui->LVL4->setValue(0);
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL4 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL2 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL3 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void Sniffer_Settings_Form::on_LVL2_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL2 = arg1;

    if (arg1 > 0)
    {
        ui->LVL3->setEnabled(true);
    }
    else
    {
        ui->LVL3->setEnabled(false); ui->LVL3->setValue(0);
        ui->LVL4->setEnabled(false); ui->LVL4->setValue(0);
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL4 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL3 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void Sniffer_Settings_Form::on_LVL3_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL3 = arg1;

    if (arg1 > 0)
    {
        ui->LVL4->setEnabled(true);
    }
    else
    {
        ui->LVL4->setEnabled(false); ui->LVL4->setValue(0);
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL4 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

   // ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void Sniffer_Settings_Form::on_LVL4_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL4 = arg1;

    if (arg1 > 0)
    {
        ui->LVL5->setEnabled(true);
    }
    else
    {
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void Sniffer_Settings_Form::on_LVL5_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL5 = arg1;

    if (arg1 > 0)
    {
        ui->LVL6->setEnabled(true);
    }
    else
    {
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void Sniffer_Settings_Form::on_LVL6_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL6 = arg1;

    if (arg1 > 0)
    {
        ui->LVL7->setEnabled(true);
    }
    else
    {
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void Sniffer_Settings_Form::on_LVL7_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL7 = arg1;

    if (arg1 > 0)
    {
        ui->LVL8->setEnabled(true);
    }
    else
    {
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void Sniffer_Settings_Form::on_LVL8_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL8 = arg1;

    if (arg1 > 0)
    {
        ui->LVL9->setEnabled(true);
    }
    else
    {
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void Sniffer_Settings_Form::on_LVL9_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL9 = arg1;

    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void Sniffer_Settings_Form::on_Stop_clicked()
{
    emit Stop_Send_Data();
}

