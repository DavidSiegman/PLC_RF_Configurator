#ifndef RESIZECALCULATING_H
#define RESIZECALCULATING_H

#include <QRect>
#include <QDebug>

class ResizeCalculating
{
public:
    ResizeCalculating();

    void set_form_geometry(QRect geometry);

    int get_text_size_1(void);
    int get_text_size_2(void);
    int get_text_size_3(void);
    int get_text_size_4(void);
    int get_text_size_5(void);

    int get_buttons_size(void);
    int get_text_edits_size(void);

    int get_icons_size(void);
private:

    QRect form_geometry;

    int text_size_1;
    int text_size_2;
    int text_size_3;
    int text_size_4;
    int text_size_5;

    int buttons_size;
    int text_edits_size;

    int icons_size;

};

#endif // RESIZECALCULATING_H
