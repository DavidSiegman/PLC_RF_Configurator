#include "resizecalculating.h"

ResizeCalculating::ResizeCalculating()
{

}

void ResizeCalculating::set_form_geometry(QRect geometry)
{
    QString s;

    this->form_geometry = geometry;

    int max_side;

    if (this->form_geometry.height() > this->form_geometry.width())
    {
        max_side = this->form_geometry.height();
    }
    else
    {
        max_side = this->form_geometry.width()*70/100;
    }

    this->text_size_1 = max_side*30/560;
    if (this->text_size_1 < 28){this->text_size_1 = 28;}
    this->text_size_2 = max_side*18/560;
    if (this->text_size_2 < 16){this->text_size_2 = 16;}
    this->text_size_3 = max_side*16/560;
    if (this->text_size_3 < 14){this->text_size_3 = 14;}
    this->text_size_4 = max_side*14/560;
    if (this->text_size_4 < 12){this->text_size_4 = 12;}
    this->text_size_5 = max_side*10/560;
    if (this->text_size_5 < 8){this->text_size_5 = 8;}

    s = "Set text_size_1: "; s += QString("%1").arg(this->text_size_1);
    qDebug() << s;
    s = "Set text_size_2: "; s += QString("%1").arg(this->text_size_2);
    qDebug() << s;
    s = "Set text_size_3: "; s += QString("%1").arg(this->text_size_3);
    qDebug() << s;
    s = "Set text_size_4: "; s += QString("%1").arg(this->text_size_4);
    qDebug() << s;
    s = "Set text_size_5: "; s += QString("%1").arg(this->text_size_5);
    qDebug() << s;

    this->buttons_size = 100;//*(this->form_geometry.width()+this->form_geometry.height())/(this->form_geometry.width()+this->form_geometry.height());

    s = "Set buttons_size: "; s += QString("%1").arg(this->buttons_size);
    qDebug() << s;

    this->icons_size = max_side*32/560;
    if (this->icons_size < 30){this->icons_size = 30;}

    s = "Set icons_size: "; s += QString("%1").arg(this->icons_size);
    qDebug() << s;
}

int ResizeCalculating::get_text_size_1()
{
    return this->text_size_1;
}

int ResizeCalculating::get_text_size_2()
{
    return this->text_size_2;
}

int ResizeCalculating::get_text_size_3()
{
    return this->text_size_3;
}

int ResizeCalculating::get_text_size_4()
{
    return this->text_size_4;
}

int ResizeCalculating::get_text_size_5()
{
    return this->text_size_5;
}

int ResizeCalculating::get_buttons_size(void)
{
    return this->buttons_size;
}
int ResizeCalculating::get_text_edits_size(void)
{
    return this->text_edits_size;
}

int ResizeCalculating::get_icons_size(void)
{
    return this->icons_size;
}
