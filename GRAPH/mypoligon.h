#ifndef MYPOLIGON_H
#define MYPOLIGON_H

#include <QObject>
#include <QPolygon>
#include <QColor>
#include "mygraphscene.h"
#include <qmath.h>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include "mygraphlegend.h"

class myPoligon: public QObject
{
    Q_OBJECT
public:
    myPoligon(QString name, int Id, QObject *parent = 0);
    void setPointsVisible(bool Visible);
    QList<QGraphicsEllipseItem*> points;
    QList<QGraphicsLineItem*> lines;
    qreal CurveWidth, PointWidth, PointRadius;
    bool PointsVisible;
    bool LegendEnable;
    QColor CurveColor, PointColor, BrushColor;
    int PointNumb;
    int PolygonId;
    myGraphLegend *legend;



public slots:
    void drawPolygon(QPolygonF *newPolygon, myGraphScene *scene);
    void removePolygon(myGraphScene *scene);

private:
    qreal my_rand(int accuracy);

};

#endif // MYPOLIGON_H
