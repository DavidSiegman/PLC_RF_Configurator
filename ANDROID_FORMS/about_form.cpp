#include "about_form.h"
#include "connections_form.h"

About_Form::About_Form(QWidget *parent) :
    myFormAbstractClass(parent){
    ui = new Ui::About_Form;
    ui->setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style);
    ui->scrollArea->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    //ui->console->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->DownPanel_Widget->setStyleSheet(DownPanel_Widget_Style);

    ui->AppName->setStyleSheet(Basic_Text_Style);
    ui->AppName->setText(APPLICATION_NAME);
    ui->label_3->setStyleSheet(Basic_Text_Style);
    ui->label_4->setStyleSheet(Basic_Text_Style);
    ui->label_5->setStyleSheet(Basic_Text_Style);

    ui->BuildingVersion->setStyleSheet(Basic_Text_Style + Text_Green);
    ui->BuildingCRC->setStyleSheet(Basic_Text_Style + Text_Green);
    ui->BuildingTime->setStyleSheet(Basic_Text_Style + Text_Green);

    ui->BuildingVersion->setText(BUILDING_VERSION);
    ui->BuildingCRC->setText(BUILDING_CRC);
    ui->BuildingTime->setText(BUILDING_TIME);

    ui->Back->setStyleSheet(PushButtons_Style+ToolTip_Style);
    ui->None->setStyleSheet(PushButtons_Style);
    ui->Apply->setStyleSheet(PushButtons_Style);

    ui->Back->setEnabled(false);
    ui->None->setEnabled(false);
}

About_Form::~About_Form(){
    delete ui;
}
void About_Form::ForceClose(){
    this->ForceCloseHandler();
}

void About_Form::resizeEvent(QResizeEvent *event){
    resize_calculating.set_form_geometry(this->geometry());

    int text_size_1 = resize_calculating.get_text_size_1();
    int text_size_2 = resize_calculating.get_text_size_2();
    //int text_size_3 = resize_calculating.get_text_size_3();
    int text_size_4 = resize_calculating.get_text_size_4();
    //int text_size_5 = resize_calculating.get_text_size_5();

    QSize icons_size;
    icons_size.setWidth(resize_calculating.get_icons_size());
    icons_size.setHeight(resize_calculating.get_icons_size());

    QFont font_1 = ui->label_1->font();        font_1.setPixelSize(text_size_1);
    QFont font_2 = ui->AppName->font();        font_2.setPixelSize(text_size_2);
    QFont font_3 = ui->label_3->font();        font_3.setPixelSize(text_size_4);

    ui->label_1->setFont(font_1);
    ui->AppName->setFont(font_2);
    ui->label_2->setFont(font_3);
    ui->label_3->setFont(font_3);
    ui->label_4->setFont(font_3);
    ui->label_5->setFont(font_3);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Apply->setIconSize(icons_size); ui->Apply->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->label_1->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
}

void About_Form::on_Apply_clicked(){
    this->Back_ClickHandler();
    emit Cancel(this->geometry());
    this->deleteLater();
}
