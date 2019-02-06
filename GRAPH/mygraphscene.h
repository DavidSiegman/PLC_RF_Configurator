#ifndef MYGRAPHSCENE_H
#define MYGRAPHSCENE_H

#include <qgraphicsscene.h>
#include "mygraphgrid.h"
#include <QLineEdit>
#include <QLabel>
#include <QEvent>
#include <qmath.h>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsSceneMouseEvent>

class myGraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    qreal x_div, y_div;
    double X_GridPixStep, Y_GridPixStep;

    explicit myGraphScene(QObject *parent);

protected:
    void wheelEvent ( QGraphicsSceneWheelEvent * wheelEvent);
    //void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent);

private:
    //QList<myPoligon*> polygons;
    myGraphGrid *mygrid;
    QLineEdit   *x_devision,       *y_devision,       *grpixstep;
    QLabel      *x_devision_label, *y_devision_label, *grpixstep_label;
    qreal        x_mult,            y_mult,            g_mult;

    int x_AxesOffset;
    int y_AxesOffset;
    QPoint OXY_Point;

signals:
    void update_polygon(myGraphScene *scene);


public slots:
    void x_devision_editingFinished(QString s);
    void y_devision_editingFinished(QString s);
    void grpixstep_editingFinished(QString s);

    void setGeometry(qreal w, qreal h);
    void setGrid(void);
    void setX_AxesOffset(int offset);
    void setY_AxesOffset(int offset);
    void setOXYPoint(QPoint OXY_Point);
    QPoint getOXYPoint(void);

    qreal getXDevision(void);
    qreal getYDevision(void);
    qreal getXGridPixStep(void);
    qreal getYGridPixStep(void);
    qreal my_rand(int accuracy);
};

#endif // MYGRAPHSCENE_H
