#include "mygraphgrid.h"
#include "mygraphscene.h"
#include "qpainter.h"

myGraphGrid::myGraphGrid():QGraphicsItem()
{
    axes_color = QColor::fromRgbF(0,0,0,1);
    axes_width = 2;
    grid_color = QColor::fromRgbF(0,0,0,0.5);
    grid_width = 1;
    x_division = 10; y_division = 0.1;

    OXY_Point.setX(0);
    OXY_Point.setY(0);
}

QRectF myGraphGrid::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF((-width - penWidth)/2, (-height - penWidth)/2, width + penWidth, height + penWidth);
}

void myGraphGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    this->setWidth(this->scene()->sceneRect().width());
    this->setHeight(this->scene()->sceneRect().height());

    // Y/X OS ==========================================================================================
    QPen p;
    p.setColor(axes_color);
    p.setWidth(axes_width);
    painter->setPen(p);
    painter->drawLine(OXY_Point.x(),-height/2,OXY_Point.x(),height/2); // y axes
    painter->drawLine(-width/2,OXY_Point.y(),width/2,OXY_Point.y());   // х axes

    painter->drawText(OXY_Point.x()-12,OXY_Point.y()+12, "0");
    // =================================================================================================
    p.setColor(grid_color);
    p.setStyle(Qt::DotLine);
    painter->setPen(p);
    // x-grid ==========================================================================================
    int _2width_ind = 0;
    int text_index = 1;
    int minus_x_grid_lage = OXY_Point.x();
    while (minus_x_grid_lage > (-width/2))
    {
        if (_2width_ind >= 10)
        {
            p.setStyle(Qt::SolidLine);
            p.setWidth(grid_width*1.5);
            painter->setPen(p);
            _2width_ind = 0;

            //painter->drawText(minus_x_grid_lage+3,OXY_Point.y()+12, QString::number(-text_index*10*x_division));
            text_index++;

        }
        else
        {
            p.setStyle(Qt::DotLine);
            p.setWidth(grid_width*0.1);
            painter->setPen(p);
        }
        painter->drawLine(minus_x_grid_lage,-(height)/2,minus_x_grid_lage,(height)/2);
        minus_x_grid_lage = minus_x_grid_lage - x_grid_pix_stepp;
        _2width_ind++;
    }
    _2width_ind = 0;
    text_index = 1;
    int plus_x_grid_lage = OXY_Point.x();
    while (plus_x_grid_lage < (width/2))
    {
        if (_2width_ind >= 10)
        {
            p.setStyle(Qt::SolidLine);
            p.setWidth(grid_width*1.5);
            painter->setPen(p);
            _2width_ind = 0;

            //painter->drawText(plus_x_grid_lage+3,OXY_Point.y()+12, QString::number(text_index*10*x_division));
            text_index++;
        }
        else
        {
            p.setStyle(Qt::DotLine);
            p.setWidth(grid_width*0.1);
            painter->setPen(p);
        }
        painter->drawLine(plus_x_grid_lage,-(height)/2,plus_x_grid_lage,(height)/2);
        plus_x_grid_lage = plus_x_grid_lage + x_grid_pix_stepp;
        _2width_ind++;
    }
    // =================================================================================================
    // y-grid ==========================================================================================
    _2width_ind = 0;
    text_index = 1;
    int minus_y_grid_lage = OXY_Point.y();
    while (minus_y_grid_lage > -(height/2))
    {
        if (_2width_ind >= 10)
        {
            p.setStyle(Qt::SolidLine);
            p.setWidth(grid_width*1.5);
            painter->setPen(p);
            _2width_ind = 0;

            painter->drawText(OXY_Point.x()-30,minus_y_grid_lage+12, QString::number(text_index*10*y_division));
            text_index++;
        }
        else
        {
            p.setStyle(Qt::DotLine);
            p.setWidth(grid_width*0.1);
            painter->setPen(p);
        }
        painter->drawLine(-width/2,minus_y_grid_lage,width/2,minus_y_grid_lage);
        minus_y_grid_lage = minus_y_grid_lage - y_grid_pix_stepp;
        _2width_ind++;
    }
    _2width_ind = 0;
    text_index = 1;
    int plus_y_grid_lage = OXY_Point.y();
    while (plus_y_grid_lage < (height)/2)
    {
        if (_2width_ind >= 10)
        {
            p.setStyle(Qt::SolidLine);
            p.setWidth(grid_width*1.5);
            painter->setPen(p);
            _2width_ind = 0;

            painter->drawText(OXY_Point.x()-30,plus_y_grid_lage-3, QString::number(-text_index*10*y_division));
            text_index++;
        }
        else
        {
            p.setStyle(Qt::DotLine);
            p.setWidth(grid_width*0.1);
            painter->setPen(p);
        }
        painter->drawLine(-width/2,plus_y_grid_lage,width/2,plus_y_grid_lage);
        plus_y_grid_lage = plus_y_grid_lage + y_grid_pix_stepp;
        _2width_ind++;
    }
    // =================================================================================================
}

void myGraphGrid::setHeight(int newHeight)
{
    if (this->height != newHeight)
    {
        prepareGeometryChange();
        this->height = newHeight;


    }
}
void myGraphGrid::setWidth(int newWidth)
{
    if (this->width != newWidth)
    {
        prepareGeometryChange();
        this->width = newWidth;
    }
}
void myGraphGrid::setXGridPixStep(double newXGridPixStep){
    this->x_grid_pix_stepp = newXGridPixStep;
}
void myGraphGrid::setYGridPixStep(double newYGridPixStep){
    this->y_grid_pix_stepp = newYGridPixStep;
}
void myGraphGrid::setAxesColor(QColor newAxesColor){
    this->axes_color = newAxesColor;
}
void myGraphGrid::setGridColor(QColor newGridColor){
    this->grid_color = newGridColor;
}
void myGraphGrid::setAxesWidth(qreal newAxesWidth){
    this->axes_width = newAxesWidth;
}
void myGraphGrid::setGridWidth(qreal newGridWidth){
    this->grid_width = newGridWidth;
}
void myGraphGrid::setXDivision(qreal newXDivision){
    this->x_division = newXDivision;
    this->scene()->update();
}
void myGraphGrid::setYDivision(qreal newYDivision){
    this->y_division = newYDivision;
    this->scene()->update();
}
void myGraphGrid::setOXYPoint(QPoint OXY_Point)
{
    this->OXY_Point = OXY_Point;
}

