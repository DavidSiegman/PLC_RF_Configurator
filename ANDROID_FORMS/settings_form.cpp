#include "settings_form.h"
#include "connections_form.h"


Settings_Form::Settings_Form(QWidget *parent) :
    myFormAbstractClass(parent){
    ui = new Ui::Settings_Form;
    ui->setupUi(this);
    this->setWindowTitle((QString)(APPLICATION_NAME) + " " + BUILDING_VERSION);
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    ui->Repeat->setValue(settings.value(CONNECTION_SETTINGS_REPEATE).toInt());
    ui->Periode->setValue(settings.value(CONNECTION_SETTINGS_PERIODE).toInt());

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style);
    ui->DownPanel_Widget->setStyleSheet(DownPanel_Widget_Style);

    ui->label_2->setStyleSheet(Basic_Text_Style);
    ui->label_3->setStyleSheet(Basic_Text_Style);

    ui->btnCOMSettings->setStyleSheet(Basic_PushButtons_Style);
    ui->btnAbout->setStyleSheet(Basic_PushButtons_Style);

    ui->Back->setStyleSheet(PushButtons_Style);
    ui->None->setStyleSheet(PushButtons_Style);
    ui->Apply->setStyleSheet(PushButtons_Style);

    ui->None->setEnabled(false);

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
Settings_Form::~Settings_Form(){
    emit Get_Console(NULL);
    delete ui;
}
void Settings_Form::on_Back_clicked(){
    this->Back_ClickHandler();
    emit Cancel(this->geometry());
    this->deleteLater();
}
void Settings_Form::ForceClose(void){
    this->ForceCloseHandler();
}
void Settings_Form::resizeEvent(QResizeEvent *event){
    resize_calculating.set_form_geometry(this->geometry());

    int text_size_1 = resize_calculating.get_text_size_1();
    int text_size_2 = resize_calculating.get_text_size_2();
    int text_size_3 = resize_calculating.get_text_size_3();
    //int text_size_4 = resize_calculating.get_text_size_4();
    //int text_size_5 = resize_calculating.get_text_size_5();

    QSize icons_size;
    icons_size.setWidth(resize_calculating.get_icons_size());
    icons_size.setHeight(resize_calculating.get_icons_size());

    QFont font_1 = ui->label_1->font();        font_1.setPixelSize(text_size_1);
    QFont font_2 = ui->label_2->font();        font_2.setPixelSize(text_size_2);
    QFont font_3 = ui->btnCOMSettings->font(); font_3.setPixelSize(text_size_3);


    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_3);
    ui->label_3->setFont(font_3);

    ui->Repeat->setFont(font_3);
    ui->RepeatSlider->setMaximumHeight(text_size_3);
    ui->Periode->setFont(font_3);
    ui->PeriodeSlider->setMaximumHeight(text_size_3);

    ui->btnCOMSettings->setFont(font_3);
    ui->btnAbout->setFont(font_3);

    QScrollBar *VerticalScrollBar = new QScrollBar(); VerticalScrollBar->setStyleSheet(ScrollBar_Style);

    ui->scrollArea->setVerticalScrollBar(VerticalScrollBar);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Apply->setIconSize(icons_size); ui->Apply->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
}

void Settings_Form::on_Apply_clicked(){
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(CONNECTION_SETTINGS_REPEATE, ui->Repeat->value());
    settings.setValue(CONNECTION_SETTINGS_PERIODE, ui->Periode->value());
    settings.sync();

    emit GetRepeatNumber(ui->Repeat->value());
    emit GetRepeatTimeout(ui->Periode->value());
    this->Back_ClickHandler();
    emit Cancel(this->geometry());
    this->deleteLater();
}
void Settings_Form::on_RepeatSlider_valueChanged(int value){
    ui->Repeat->setValue(value);
}
void Settings_Form::on_PeriodeSlider_valueChanged(int value){
    value *= 100;
    ui->Periode->setValue(value);
}
void Settings_Form::on_Repeat_valueChanged(int arg1){
    int SliderValue = arg1;
    ui->RepeatSlider->setValue(SliderValue);
}
void Settings_Form::on_Periode_valueChanged(int arg1){
    int SliderValue = arg1/100;
    ui->PeriodeSlider->setValue(SliderValue);
}
void Settings_Form::on_btnAbout_clicked(){
    emit Open_AboutWindow(this);
}
