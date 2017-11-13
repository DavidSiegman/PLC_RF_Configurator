#include "mygraphlegend.h"
#include "mygraphscene.h"
#include "qpainter.h"
#include "mypoligon.h"

myGraphLegend::myGraphLegend(myPoligon *polygon) : QGraphicsItem()
{
    this->setFlag(QGraphicsItem::ItemIsMovable,true);
    this->setFlag(QGraphicsItem::ItemClipsToShape,true);
    this->setFlag(QGraphicsItem::ItemClipsChildrenToShape,true);

    myPolygon = polygon;
}

QRectF myGraphLegend::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(0,0, width, height);
}

void myGraphLegend::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int textLength = LegendeText.length();

    this->setWidth(50+textLength*6);
    this->setHeight(20);

    // BackGround
    QBrush b_background;
    b_background.setColor(QColor::fromRgbF(1,1,1,0.24));
    b_background.setStyle(Qt::SolidPattern);
    painter->setBrush(b_background);

    QPen p;
    p.setColor(QColor::fromRgbF(1,1,1,1));
    //p.setWidth(axes_width);
    painter->setPen(p);
    painter->drawRect(0,0,width, height);

    b_background.setColor(QColor::fromRgbF(0,0,0,1));
    p.setColor(QColor::fromRgbF(0,0,0,1));
    painter->setPen(p);
    painter->setBrush(b_background);
    painter->drawText(50,height/2+4,LegendeText);

    p.setColor(this->myPolygon->CurveColor);
    p.setWidthF(this->myPolygon->CurveWidth);
    painter->setPen(p);
    painter->drawLine(5,(int)(height/2+this->myPolygon->CurveWidth/2), 45,(int)(height/2+this->myPolygon->CurveWidth/2));

    if (this->myPolygon->PointsVisible == true)
    {
        p.setColor(this->myPolygon->PointColor);
        p.setWidth(this->myPolygon->PointWidth);
        painter->setPen(p);
        b_background.setColor(this->myPolygon->BrushColor);
        painter->setBrush(b_background);
        painter->drawEllipse(20,height/2-5,10,10);
    }

}

void myGraphLegend::setHeight(int newHeight)
{
    if (this->height != newHeight)
    {
        prepareGeometryChange();
        this->height = newHeight;
    }
}
void myGraphLegend::setWidth(int newWidth)
{
    if (this->width != newWidth)
    {
        prepareGeometryChange();
        this->width = newWidth;
    }
}

void myGraphLegend::setTexte(QString newLegendeText)
{
    this->LegendeText = newLegendeText;
}

int myGraphLegend::getHeight(void)
{
    int result = 0;
    result = height;
    return result;
}
int myGraphLegend::getWidth(void)
{
    int result = 0;
    result = width;
    return result;
}
