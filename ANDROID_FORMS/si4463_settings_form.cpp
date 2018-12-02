#include "si4463_settings_form.h"
#include "ui_si4463_settings_form.h"

SI4463_Settings_Form::SI4463_Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI4463_Settings_Form)
{
    ui->setupUi(this);

    connect(ui->ClearConsole,  SIGNAL(clicked(bool)),         ui->console, SLOT(clear()));

}

SI4463_Settings_Form::~SI4463_Settings_Form()
{
    delete ui;
}

void SI4463_Settings_Form::resizeEvent(QResizeEvent *event)
{
    emit isCreated();
}

void SI4463_Settings_Form::on_Back_clicked()
{
    emit Get_Console(NULL);
    emit Cancel(this->geometry());
}

void SI4463_Settings_Form::on_Next_clicked()
{
    emit Get_Console(NULL);
    emit Next(this->geometry());
}

void SI4463_Settings_Form::on_btnSettings_clicked()
{
    emit Settings(this);
}

void SI4463_Settings_Form::SetProgress(uint progress)
{
    ui->progress->setValue(progress);
}

void SI4463_Settings_Form::Set_Geometry(QRect new_value)
{
    this->setGeometry(new_value);
}

void SI4463_Settings_Form::Set_Model(QStandardItemModel *model)
{
    ui->SI4436_PROPSView      ->setModel(model);
    ui->SI4436_PROPSView      ->resizeRowsToContents();
    ui->SI4436_PROPSView      ->resizeColumnsToContents();
}

void SI4463_Settings_Form::Set_Prameters(QList<Params> *params)
{
    int index = 0;
    for(int i = 0; i < params->length();i++)
    {
        if(params->at(i).name.compare("Rsymb(sps):") == 0)
        {
            ui->DataRate->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("RF Freq.(MHz):") == 0)
        {
            ui->Freq->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("MOD_type:") == 0)
        {
            ui->MODULATION->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("Fdev(Hz):") == 0)
        {
            ui->Fdev->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("RXBW(Hz):") == 0)
        {
            ui->RXBW->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("AFC_en:") == 0)
        {
            ui->AFC_State->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("WB filter ") == 0)
        {
            ui->WB_Filter->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("NB-filter ") == 0)
        {
            index = 1;
            ui->NB_Filter->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("NB-filter ") == 0)
        {
            ui->NB_Filter->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("BW =  ") == 0)
        {
            ui->WB_BW->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("BW = ") == 0)
        {
           ui->NB_BW->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("Modulation index:") == 0)
        {
            ui->MOD_INDEX->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("ANT_DIV:") == 0)
        {
            ui->ANT_DIV->setText(params->at(i).value);
        }

    }
    ui->Write->setEnabled(true);
}

void SI4463_Settings_Form::on_Stop_clicked()
{
    emit Get_Console(ui->console);

    emit Stop_Send_Data();
}

void SI4463_Settings_Form::isStopped()
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}

void SI4463_Settings_Form::on_Reset_clicked()
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

void SI4463_Settings_Form::isRF_Reset()
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}

void SI4463_Settings_Form::isSI4463_Parameters()
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}


void SI4463_Settings_Form::on_FileOpen_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.txt");

    QString s = "";
    for(uint i = (str.length()); i > 0; i--)
    {
        if (str.at(i-1) != '/')
        {
            s.push_front(str.at(i-1));
        }
        else
        {
            break;
        }
    }

    ui->FileName->setText(s);

    emit Start_Parcer(str);
}

void SI4463_Settings_Form::on_Write_clicked()
{
    emit Get_Console(ui->console);
    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit Write_SI4463_Parameters();
}
