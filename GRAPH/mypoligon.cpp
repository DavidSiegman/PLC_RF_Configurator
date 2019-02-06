#include "mypoligon.h"

myPoligon::myPoligon(QString name, int Id, QObject *parent) : QObject(parent)
{
    PointNumb = 0;
    CurveWidth = 2;
    CurveColor = QColor::fromRgbF(0.5,0.3,0,1);
    BrushColor = QColor::fromRgbF(1,0.5,0.8,1);
    //BrushColor = QColor::fromRgbF(my_rand(2),my_rand(2),my_rand(2),1);

    PointRadius = 4;
    PointWidth = 1.8;

    PointsVisible = true;

    QObject::connect(parent, SIGNAL(update_polygon(myGraphScene*)),this,SLOT(drawPolygon(myGraphScene*)));

    LegendEnable = false;
    legend = new myGraphLegend(this);
    legend->setZValue(1000);
    legend->setTexte(name);

    PolygonId = Id;
}

void myPoligon::drawPolygon(QPolygonF *newPolygon, myGraphScene *scene)
{
    QString String (   "QToolTip{"
                        "color: rgb(255,255,220);"
                        "border-style: none;"
                        "border-width: 1px;"
                        "border-color: rgba(255,220,180,255);"
                        "background: rgba(100,50,00,255);"
                        "}"
                    );

    PointNumb = newPolygon->size();
    PointRadius = scene->Y_GridPixStep/3;

    removePolygon(scene);
    //points.reserve(PointNumb);
    //lines.reserve(PointNumb-1);

    // рисование полигона
    QPen p_curve;
    p_curve.setColor(this->CurveColor);
    p_curve.setWidth(this->CurveWidth);
    QPen p_point;
    p_point.setColor(this->PointColor);
    p_point.setWidth(this->PointWidth);
    QBrush b_point;
    b_point.setStyle(Qt::SolidPattern);
    b_point.setColor(BrushColor);

    for(int j = 0; j < this->PointNumb; j++)
    {
        int x_coordinate = newPolygon->at(j).x()/scene->x_div*scene->X_GridPixStep + scene->getOXYPoint().x();
        int y_coordinate = newPolygon->at(j).y()/scene->y_div*scene->Y_GridPixStep - scene->getOXYPoint().y();

        if ((newPolygon->at(j).y()) <= 0 && (newPolygon->at(j).y() > -1*26)){
            b_point.setColor(QColor::fromRgb(60,180,5,255));
            p_curve.setColor(QColor::fromRgb(60,180,5,255));
        }
        else if ((newPolygon->at(j).y()) <= -1*26 && (newPolygon->at(j).y() > -2*26)){
            b_point.setColor(QColor::fromRgb(120,180,5,255));
            p_curve.setColor(QColor::fromRgb(120,180,5,255));
        }
        else if ((newPolygon->at(j).y()) <= -2*26 && (newPolygon->at(j).y() > -3*26)){
            b_point.setColor(QColor::fromRgb(180,180,5,255));
            p_curve.setColor(QColor::fromRgb(180,180,5,255));
        }
        else if ((newPolygon->at(j).y()) <= -3*26 && (newPolygon->at(j).y() > -4*26)){
            b_point.setColor(QColor::fromRgb(180,120,5,255));
            p_curve.setColor(QColor::fromRgb(180,120,5,255));
        }
        else if ((newPolygon->at(j).y()) <= -4*26 && (newPolygon->at(j).y() > -5*26)){
            b_point.setColor(QColor::fromRgb(180,60,5,255));
            p_curve.setColor(QColor::fromRgb(180,60,5,255));
        }
        else{
            b_point.setColor(QColor::fromRgb(180,0,0,255));
            p_curve.setColor(QColor::fromRgb(180,0,0,255));
        }

        if (j >= 1)
        {
            int x0_coordinate = newPolygon->at(j-1).x()/scene->x_div*scene->X_GridPixStep + scene->getOXYPoint().x();
            int y0_coordinate = newPolygon->at(j-1).y()/scene->y_div*scene->Y_GridPixStep - scene->getOXYPoint().y();

            QGraphicsLineItem *line = scene->addLine(x0_coordinate,-y0_coordinate,x_coordinate,-y_coordinate,p_curve);
            line->setZValue(-2);
            this->lines.append(line);

            if (this->PointsVisible == true)
            {
                QGraphicsEllipseItem *elipse = scene->addEllipse(x0_coordinate-PointRadius/2,-y0_coordinate-PointRadius/2,PointRadius,PointRadius,p_point,b_point);
                elipse->setToolTip("x: " + QString::number(newPolygon->at(j-1).x()) +
                                  " y: " + QString::number(newPolygon->at(j-1).y()));
                this->points.append(elipse);
            }
        }
    }

    if (PointNumb > 1)
    {
        if (this->PointsVisible == true)
        {
            int x_c = newPolygon->at(PointNumb-1).x()/scene->x_div*scene->X_GridPixStep + scene->getOXYPoint().x();
            int y_c = newPolygon->at(PointNumb-1).y()/scene->y_div*scene->Y_GridPixStep - scene->getOXYPoint().y();

            if ((newPolygon->at(PointNumb-1).y()) <= 0 && (newPolygon->at(PointNumb-1).y() > -1*26)){
                b_point.setColor(QColor::fromRgb(60,180,5,255));
                p_curve.setColor(QColor::fromRgb(60,180,5,255));
            }
            else if ((newPolygon->at(PointNumb-1).y()) <= -1*26 && (newPolygon->at(PointNumb-1).y() > -2*26)){
                b_point.setColor(QColor::fromRgb(120,180,5,255));
                p_curve.setColor(QColor::fromRgb(120,180,5,255));
            }
            else if ((newPolygon->at(PointNumb-1).y()) <= -2*26 && (newPolygon->at(PointNumb-1).y() > -3*26)){
                b_point.setColor(QColor::fromRgb(180,180,5,255));
                p_curve.setColor(QColor::fromRgb(180,180,5,255));
            }
            else if ((newPolygon->at(PointNumb-1).y()) <= -3*26 && (newPolygon->at(PointNumb-1).y() > -4*26)){
                b_point.setColor(QColor::fromRgb(180,120,5,255));
                p_curve.setColor(QColor::fromRgb(180,120,5,255));
            }
            else if ((newPolygon->at(PointNumb-1).y()) <= -4*26 && (newPolygon->at(PointNumb-1).y() > -5*26)){
                b_point.setColor(QColor::fromRgb(180,60,5,255));
                p_curve.setColor(QColor::fromRgb(180,60,5,255));
            }
            else{
                b_point.setColor(QColor::fromRgb(180,0,0,255));
                p_curve.setColor(QColor::fromRgb(180,0,0,255));
            }

            QGraphicsEllipseItem *elipse = scene->addEllipse(x_c-PointRadius/2,-y_c-PointRadius/2,PointRadius,PointRadius,p_point,b_point);
            elipse->setZValue(-1);
            elipse->setToolTip("x: " + QString::number(newPolygon->at(PointNumb-1).x()) +
                              " y: " + QString::number(newPolygon->at(PointNumb-1).y()));
            this->points.append(elipse);
        }
    }
    if (LegendEnable == true)
    {
        legend->setX(-scene->width()/2+20);
        legend->setY(-scene->height()/2+25+25*PolygonId);
        scene->addItem(legend);
    }

}
void myPoligon::removePolygon(myGraphScene *scene)
{
    // удаление полигона со сцены
    if (this->points.isEmpty() == false)
    {
        for(int j = 0; j < this->points.length(); j++)
        {
            scene->removeItem(this->points.at(j));
        }
    }
    if (this->lines.isEmpty() == false)
    {
        for(int i = 0; i < this->lines.length(); i++)
        {
            scene->removeItem(this->lines.at(i));
        }
    }
    // очистка контейнеров
    this->points.clear();
    this->lines.clear();
}
double myPoligon::my_rand(int accuracy)
{
  double a = 0;
  a = (qrand() % int (qPow(10, accuracy) + 1))/qPow(10, accuracy);
  return a;
}

void myPoligon::setPointsVisible(bool Visible)
{
    this->PointsVisible = Visible;
}

void myPoligon::addPointWithXOffset(QPolygonF *newPolygon, QPoint point, qreal x_offset, qreal x_endpoint)
{
    int    PointsNumber = newPolygon->size();
    qreal current_x;
    QPoint p;
    if (PointsNumber > 0){
        for(int i = 0; i < PointsNumber; i++){
            current_x = newPolygon->at(i).x() + x_offset;

            if (((x_endpoint < 0)&&(current_x < x_endpoint)) ||
                ((x_endpoint >= 0)&&(current_x > x_endpoint))){
                newPolygon->removeAt(i);
                PointsNumber--;
            }
            else {
                p.setX(current_x);
                p.setY(newPolygon->at(i).y());
                newPolygon->replace(i,p);
            }
        }
    }
    newPolygon->append(point);
}


