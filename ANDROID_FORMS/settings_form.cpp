#include "settings_form.h"
#include "connections_form.h"
#include "ui_settings_form.h"

Settings_Form::Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings_Form)
{
    ui->setupUi(this);
    this->setWindowTitle(APPLICATION_NAME);
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    ui->Repeat->setText(settings.value(CONNECTION_SETTINGS_REPEATE).toString());
    ui->Periode->setText(settings.value(CONNECTION_SETTINGS_PERIODE).toString());

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style);


    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style);

    ui->label_2->setStyleSheet(Basic_Text_Style);
    ui->label_3->setStyleSheet(Basic_Text_Style);

    ui->btnCOMSettings->setStyleSheet(Basic_Buttons_Style);

    ui->Back->setStyleSheet(Buttons_Style);
    ui->Apply->setStyleSheet(Buttons_Style);

    ui->Repeat->setStyleSheet(Background_White+Basic_Text_Style);
    ui->Periode->setStyleSheet(Background_White+Basic_Text_Style);

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
}


void Settings_Form::resizeEvent(QResizeEvent *event)
{
    resize_calculating.set_form_geometry(this->geometry());

    int text_size_1 = resize_calculating.get_text_size_1();
    int text_size_2 = resize_calculating.get_text_size_2();
    int text_size_3 = resize_calculating.get_text_size_3();
    //int text_size_4 = resize_calculating.get_text_size_4();
    //int text_size_5 = resize_calculating.get_text_size_5();

    QSize icons_size;
    icons_size.setWidth(resize_calculating.get_icons_size());
    icons_size.setHeight(resize_calculating.get_icons_size());

    QFont font_1 = ui->label_1->font();    font_1.setPixelSize(text_size_1);
    QFont font_2 = ui->label_2->font();    font_2.setPixelSize(text_size_2);
    QFont font_3 = ui->btnCOMSettings->font();     font_3.setPixelSize(text_size_3);


    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_3);
    ui->label_3->setFont(font_3);

    ui->Repeat->setFont(font_3);
    ui->Periode->setFont(font_3);

    ui->btnCOMSettings->setFont(font_3);

    QScrollBar *VerticalScrollBar = new QScrollBar(); VerticalScrollBar->setStyleSheet(ScrollBar_Style);

    ui->scrollArea->setVerticalScrollBar(VerticalScrollBar);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Apply->setIconSize(icons_size); ui->Apply->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
}

Settings_Form::~Settings_Form()
{
    delete ui;
}

void Settings_Form::on_Back_clicked()
{
    emit Get_Geometry(this->geometry());
    emit Cancel();
    this->deleteLater();
}

void Settings_Form::on_Apply_clicked()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(CONNECTION_SETTINGS_REPEATE, ui->Repeat->text());
    settings.setValue(CONNECTION_SETTINGS_PERIODE, ui->Periode->text());
    settings.sync();

    emit GetRepeatNumber(ui->Repeat->text().toInt());
    emit GetRepeatTimeout(ui->Periode->text().toInt());
    emit Cancel();
    this->deleteLater();
}
