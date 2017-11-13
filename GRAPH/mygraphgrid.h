#ifndef MYGRAPHGRID_H
#define MYGRAPHGRID_H

#include "qgraphicsitem.h"

class myGraphGrid : public QGraphicsItem
{
public:
    myGraphGrid();
    void setHeight(int newHeight);
    void setWidth(int newWidth);
    void setGridPixStep(int newGridPixStep);
    void setAxesColor(QColor newAxesColor);
    void setGridColor(QColor newGridColor);
    void setAxesWidth(qreal newAxesWidth);
    void setGridWidth(qreal newGridWidth);
    void setXDivision(qreal newXDivision);
    void setYDivision(qreal newYDivision);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int width, height;
    int grid_pix_stepp;
    QColor axes_color, grid_color;
    qreal axes_width, grid_width;
    qreal x_division, y_division;
};

#endif // MYGRAPHGRID_H
