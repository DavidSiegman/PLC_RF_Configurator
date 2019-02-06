#ifndef MYGRAPHGRID_H
#define MYGRAPHGRID_H

#include "qgraphicsitem.h"

class myGraphGrid : public QGraphicsItem
{
public:
    myGraphGrid();
    void setHeight(int newHeight);
    void setWidth(int newWidth);
    void setXGridPixStep(double newXGridPixStep);
    void setYGridPixStep(double newYGridPixStep);
    void setAxesColor(QColor newAxesColor);
    void setGridColor(QColor newGridColor);
    void setAxesWidth(qreal newAxesWidth);
    void setGridWidth(qreal newGridWidth);
    void setXDivision(qreal newXDivision);
    void setYDivision(qreal newYDivision);
    void setOXYPoint(QPoint OXY_Point);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int width, height;
    double x_grid_pix_stepp, y_grid_pix_stepp;
    QPoint OXY_Point;
    QColor axes_color, grid_color;
    qreal axes_width, grid_width;
    qreal x_division, y_division;
};

#endif // MYGRAPHGRID_H
