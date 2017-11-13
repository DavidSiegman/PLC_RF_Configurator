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
    explicit myGraphScene(QObject *parent);
    void setGeometry(qreal w, qreal h);
    qreal getXDevision(void);
    qreal getYDevision(void);
    qreal getGridPixStep(void);
    qreal my_rand(int accuracy);
    void setGrid(void);
    qreal x_div, y_div;
    int GridPixStep;

protected:
    void wheelEvent ( QGraphicsSceneWheelEvent * wheelEvent);
    //void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent);

private:
    //QList<myPoligon*> polygons;
    myGraphGrid *mygrid;
    QLineEdit *x_devision, *y_devision, *grpixstep;
    QLabel *x_devision_label, *y_devision_label, *grpixstep_label;
    qreal x_mult, y_mult, g_mult;

signals:
    void update_polygon(myGraphScene *scene);


public slots:
    void x_devision_editingFinished(QString s);
    void y_devision_editingFinished(QString s);
    void grpixstep_editingFinished(QString s);
};

#endif // MYGRAPHSCENE_H
