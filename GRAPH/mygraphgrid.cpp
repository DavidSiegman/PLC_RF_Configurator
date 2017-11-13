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
    painter->drawLine(0.0,-height/2,0.0,height/2);
    painter->drawLine(-width/2,0.0,width/2,0.0);

    painter->drawText(-12,+12, "0");
    // =================================================================================================

    p.setColor(grid_color);
    p.setStyle(Qt::DotLine);
    painter->setPen(p);
    // x-grid ==========================================================================================
    int _2width_ind = 0;
    int text_index = 1;
    int minus_x_grid_lage = 0;
    while (minus_x_grid_lage > -width/2)
    {
        if (_2width_ind >= 10)
        {
            p.setStyle(Qt::SolidLine);
            p.setWidth(grid_width*1.5);
            painter->setPen(p);
            _2width_ind = 0;

            painter->drawText(minus_x_grid_lage+3,+12, QString::number(-text_index*10*x_division));
            text_index++;

        }
        else
        {
            p.setStyle(Qt::DotLine);
            p.setWidth(grid_width*0.1);
            painter->setPen(p);
        }
        painter->drawLine(minus_x_grid_lage,-height/2,minus_x_grid_lage,height/2);
        minus_x_grid_lage = minus_x_grid_lage - grid_pix_stepp;
        _2width_ind++;
    }
    _2width_ind = 0;
    text_index = 1;
    int plus_x_grid_lage = 0;
    while (plus_x_grid_lage < width/2)
    {
        if (_2width_ind >= 10)
        {
            p.setStyle(Qt::SolidLine);
            p.setWidth(grid_width*1.5);
            painter->setPen(p);
            _2width_ind = 0;

            painter->drawText(plus_x_grid_lage+3,+12, QString::number(text_index*10*x_division));
            text_index++;
        }
        else
        {
            p.setStyle(Qt::DotLine);
            p.setWidth(grid_width*0.1);
            painter->setPen(p);
        }
        painter->drawLine(plus_x_grid_lage,-height/2,plus_x_grid_lage,height/2);
        plus_x_grid_lage = plus_x_grid_lage + grid_pix_stepp;
        _2width_ind++;
    }
    // =================================================================================================
    // y-grid ==========================================================================================
    _2width_ind = 0;
    text_index = 1;
    int minus_y_grid_lage = 0;
    while (minus_y_grid_lage > -height/2)
    {
        if (_2width_ind >= 10)
        {
            p.setStyle(Qt::SolidLine);
            p.setWidth(grid_width*1.5);
            painter->setPen(p);
            _2width_ind = 0;

            painter->drawText(+3,minus_y_grid_lage+12, QString::number(text_index*10*y_division));
            text_index++;
        }
        else
        {
            p.setStyle(Qt::DotLine);
            p.setWidth(grid_width*0.1);
            painter->setPen(p);
        }
        painter->drawLine(-width/2,minus_y_grid_lage,width/2,minus_y_grid_lage);
        minus_y_grid_lage = minus_y_grid_lage - grid_pix_stepp;
        _2width_ind++;
    }
    _2width_ind = 0;
    text_index = 1;
    int plus_y_grid_lage = 0;
    while (plus_y_grid_lage < height/2)
    {
        if (_2width_ind >= 10)
        {
            p.setStyle(Qt::SolidLine);
            p.setWidth(grid_width*1.5);
            painter->setPen(p);
            _2width_ind = 0;

            painter->drawText(+3,plus_y_grid_lage-3, QString::number(-text_index*10*y_division));
            text_index++;
        }
        else
        {
            p.setStyle(Qt::DotLine);
            p.setWidth(grid_width*0.1);
            painter->setPen(p);
        }
        painter->drawLine(-width/2,plus_y_grid_lage,width/2,plus_y_grid_lage);
        plus_y_grid_lage = plus_y_grid_lage + grid_pix_stepp;
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
void myGraphGrid::setGridPixStep(int newGridPixStep)
{
    this->grid_pix_stepp = newGridPixStep;
}

void myGraphGrid::setAxesColor(QColor newAxesColor)
{
    this->axes_color = newAxesColor;
}
void myGraphGrid::setGridColor(QColor newGridColor)
{
    this->grid_color = newGridColor;
}
void myGraphGrid::setAxesWidth(qreal newAxesWidth)
{
    this->axes_width = newAxesWidth;
}
void myGraphGrid::setGridWidth(qreal newGridWidth)
{
    this->grid_width = newGridWidth;
}
void myGraphGrid::setXDivision(qreal newXDivision)
{
    this->x_division = newXDivision;
    this->scene()->update();
}
void myGraphGrid::setYDivision(qreal newYDivision)
{
    this->y_division = newYDivision;
    this->scene()->update();
}
