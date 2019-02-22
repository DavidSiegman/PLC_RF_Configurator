#include "si4463_registers_form.h"
#include "connections_form.h"
#include "ui_si4463_registers_form.h"

#include "STYLE/style.h"

SI4463_Registers_Form::SI4463_Registers_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI4463_Registers_Form)
{
    ui->setupUi(this);
    this->setWindowTitle((QString)(APPLICATION_NAME) + " " + BUILDING_VERSION);

    this->setStyleSheet(Main_Widget_Style);
    ui->DownPanel_Widget->setStyleSheet(DownPanel_Widget_Style);

    ui->SI4436_PROPSView->setStyleSheet(Work_Area_Style + Basic_Text_Style);
    ui->label_2->setStyleSheet(Work_Area_Style + Basic_Text_Style);

    ui->label_1->setStyleSheet(Titel_Widget_Style);

    ui->Back->setStyleSheet(PushButtons_Style);
    ui->btnSettings->setStyleSheet(PushButtons_Style);
    ui->Next->setStyleSheet(PushButtons_Style);
}

SI4463_Registers_Form::~SI4463_Registers_Form()
{
    delete ui;
}

void SI4463_Registers_Form::resizeEvent(QResizeEvent *event)
{
    emit isCreated();

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
    QFont font_2 = ui->label_2->font();     font_2.setPixelSize(text_size_2);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_2);


    QScrollBar *VerticalScrollBar = new QScrollBar(); VerticalScrollBar->setStyleSheet(ScrollBar_Style);
    QScrollBar *HorizontalScrollBar = new QScrollBar(); HorizontalScrollBar->setStyleSheet(ScrollBar_Style);

    ui->SI4436_PROPSView->setVerticalScrollBar(VerticalScrollBar);
    ui->SI4436_PROPSView->setHorizontalScrollBar(HorizontalScrollBar);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
}

void SI4463_Registers_Form::Set_Model(QStandardItemModel *model)
{
    ui->SI4436_PROPSView      ->setModel(model);
    ui->SI4436_PROPSView      ->resizeRowsToContents();
    ui->SI4436_PROPSView      ->resizeColumnsToContents();
}

void SI4463_Registers_Form::on_Back_clicked()
{
    emit Get_Geometry(this->geometry());
    emit Cancel();
    this->deleteLater();
}

void SI4463_Registers_Form::on_Next_clicked()
{
    emit Get_Geometry(this->geometry());
    emit Cancel();
    this->deleteLater();
}

void SI4463_Registers_Form::on_btnSettings_clicked()
{
    emit Settings(this);
}
