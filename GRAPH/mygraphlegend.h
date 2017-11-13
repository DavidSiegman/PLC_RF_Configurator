#ifndef MYGRAPHLEGEND_H
#define MYGRAPHLEGEND_H

#include "qgraphicsitem.h"
class myPoligon;
class myGraphLegend : public QGraphicsItem
{
public:
    myGraphLegend(myPoligon *polygon);
    void setHeight(int newHeight);
    void setWidth(int newWidth);
    int getHeight(void);
    int getWidth(void);
    void setTexte(QString newLegendeText);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    myPoligon *myPolygon;
    int width, height;
    QString LegendeText;
};

#endif // MYGRAPHLEGEND_H
