#include "retranslation_table_form.h"
#include "connections_form.h"

#include "STYLE/style.h"

Retranslation_Table_Form::Retranslation_Table_Form(QWidget *parent) :
    myFormAbstractClass(parent)
{
    ui = new Ui::Retranslation_Table_Form;
    ui->setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style + ToolTip_Style);
    ui->scrollArea->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->console->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->DownPanel_Widget->setStyleSheet(DownPanel_Widget_Style);

    ui->Add_NetItem->setStyleSheet(Basic_PushButtons_Style);
    ui->Del_NetItem->setStyleSheet(Basic_PushButtons_Style);
    ui->Read_NetTable->setStyleSheet(Basic_PushButtons_Style);
    ui->None->setStyleSheet(Basic_PushButtons_Style);
    ui->Del_NetTable->setStyleSheet(Basic_PushButtons_Style);
    ui->Write->setStyleSheet(Basic_PushButtons_Style);
    ui->Stop->setStyleSheet(Basic_PushButtons_Style);
    ui->Reset->setStyleSheet(Basic_PushButtons_Style);
    ui->ClearConsole->setStyleSheet(Basic_PushButtons_Style);

    ui->Back->setStyleSheet(PushButtons_Style+ToolTip_Style);
    ui->btnSettings->setStyleSheet(PushButtons_Style+ToolTip_Style);
    ui->Next->setStyleSheet(PushButtons_Style+ToolTip_Style);
    ui->Next->setEnabled(false);

    model = new QStandardItemModel;

    ui->NetTable->setModel(model);

    connect(model,             SIGNAL(itemChanged(QStandardItem*)), this,           SLOT(ModelItemChanged(QStandardItem*)));
}
void Retranslation_Table_Form::on_ClearConsole_clicked(){
    WriteLogToFile(ui->console);
    ui->console->clear();
}
Retranslation_Table_Form::~Retranslation_Table_Form(){
    emit Get_Console(NULL);
    delete ui;
}

void Retranslation_Table_Form::on_Back_clicked(){
    WriteLogToFile(ui->console);
    this->Back_ClickHandler();
    emit Cancel(this->geometry());
}
void Retranslation_Table_Form::on_Next_clicked(){
    WriteLogToFile(ui->console);
    this->Next_ClickHandler();
}
void Retranslation_Table_Form::ForceClose(void){
    WriteLogToFile(ui->console);
    this->ForceCloseHandler();
}
void Retranslation_Table_Form::on_btnSettings_clicked(){
    emit Settings(this);
}
void Retranslation_Table_Form::SetProgress(uint progress){
    ui->progress->setValue(progress);
}
void Retranslation_Table_Form::on_Stop_clicked(){
    emit Stop_Send_Data();
}
void Retranslation_Table_Form::on_Reset_clicked()
{
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Read_NetTable->setEnabled(false);
    ui->Write->setEnabled(false);
    ui->Del_NetTable->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    this->Reset_ClickHandler();
}
void Retranslation_Table_Form::isStopped(void){
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Read_NetTable->setEnabled(true);
    ui->Write->setEnabled(true);
    ui->Del_NetTable->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Retranslation_Table_Form::isRF_Reset(void)
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Read_NetTable->setEnabled(true);
    ui->Write->setEnabled(true);
    ui->Del_NetTable->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
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
    QFont font_2 = ui->label_2->font();    font_2.setPixelSize(text_size_4);
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

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->label_1->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);

    emit Get_Console(ui->console);
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
void Retranslation_Table_Form::on_Add_NetItem_clicked(){
    if (Out_Retranslator_Properties->getRetranslator_Table().length() < 100) {
        bool ok;
        int i = QInputDialog::getInt(ui->scrollAreaWidgetContents, QString::fromUtf8("Введите адресс устройства"), QString::fromUtf8(""), 1, 1, 2147483647, 1, &ok);
        if (ok){
            //emit ADD_NET_TABLE_ITEM(QString::number(i));

            QString SN = QString::number(i);
            modelChanging = 1;
            QStandardItem *item = new QStandardItem(SN);
            int model_index = Out_Retranslator_Properties->getRetranslator_Table().length();
            this->model->setItem(model_index, 0, item);
            modelChanging = 0;
            Out_Retranslator_Properties->addNewItemToRetranslation_Table(SN);
        }
    }
}
void Retranslation_Table_Form::on_Del_NetItem_clicked(){
    modelChanging = 1;
    if (this->model->rowCount() > 0){
        uint count = this->model->rowCount()-1;
        Out_Retranslator_Properties->delCurrentItemFromRetranslation_Table();
        //Out_Retranslator_Properties->setRetranslator_Table_Current_Index(count);
        this->model->removeRow(count);
        if (count == 0){
            this->model->removeColumn(0);
        }
    }
    modelChanging = 0;
}

void Retranslation_Table_Form::on_Read_NetTable_clicked(){
    emit Get_Console(ui->console);
    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Read_NetTable->setEnabled(false);
    ui->Write->setEnabled(false);
    ui->Del_NetTable->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    modelChanging = 1;
    this->model->clear();
    modelChanging = 0;
    emit StartSendingProcess(SEND_READ_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
}
void Retranslation_Table_Form::on_Write_clicked(){
    emit Get_Console(ui->console);
    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Read_NetTable->setEnabled(false);
    ui->Write->setEnabled(false);
    ui->Del_NetTable->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
}

void Retranslation_Table_Form::isSwitch_Table(void){
    emit isCreated();
    Out_Retranslator_Properties->setRetranslator_Table(In_Retranslator_Properties->getRetranslator_Table());
    this->model->clear();
    QList<QString> table = Out_Retranslator_Properties->getRetranslator_Table();
    modelChanging = 1;
    for(unsigned int i = 0; i < table.length(); i++){
        QStandardItem *item = new QStandardItem(table.at(i));
        this->model->setItem(i, 0, item);
    }
    modelChanging = 0;
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Read_NetTable->setEnabled(true);
    ui->Write->setEnabled(true);
    ui->Del_NetTable->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Retranslation_Table_Form::on_Del_NetTable_clicked(){
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Read_NetTable->setEnabled(false);
    ui->Write->setEnabled(false);
    ui->Del_NetTable->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    emit StartSendingProcess(SEND_DELET_SWITCH_TABLE,CONFIG_SEND_CONTROL);
}
void Retranslation_Table_Form::isDelet_Switch_Table(void){
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Read_NetTable->setEnabled(true);
    ui->Write->setEnabled(true);
    ui->Del_NetTable->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
    Out_Retranslator_Properties->clearRetranslation_Table();
    modelChanging = 1;
    this->model->clear();
    modelChanging = 0;
}

void Retranslation_Table_Form::ModelItemChanged(QStandardItem* item){
    if (modelChanging == 0){
    // перезагружаем модель в Out_Retranslator_Properties
        Out_Retranslator_Properties->clearRetranslation_Table();
        for(int i = 0; i < this->model->rowCount(); i++){
            Out_Retranslator_Properties->addNewItemToRetranslation_Table(model->item(i,0)->text());
        }
    }
}
