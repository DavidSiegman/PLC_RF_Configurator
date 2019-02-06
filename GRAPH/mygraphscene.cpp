#include "mygraphscene.h"

myGraphScene::myGraphScene(QObject *parent) : QGraphicsScene(parent)
{
    this->setFocus();
    this->Y_GridPixStep = 10;
    this->X_GridPixStep = 10;

    this->setGrid();

    this->x_div = 1;
    this->y_div = 13;

    x_mult = 0.01, y_mult = 0.01, g_mult = 1;

    y_AxesOffset = 0; //-this->height()/2;
    x_AxesOffset = 0; //this->width()/2;

    OXY_Point.setX(x_AxesOffset);
    OXY_Point.setY(y_AxesOffset);

    QString String (   "{"
                        "background: rgba(255,255,255,60);"
                       "}"
                    );

    this->x_devision_label = new QLabel();
    this->y_devision_label = new QLabel();
    this->grpixstep_label = new QLabel();
    x_devision_label->setStyleSheet(QString ("QLabel" + String));
    y_devision_label->setStyleSheet(QString ("QLabel" + String));
    grpixstep_label->setStyleSheet(QString ("QLabel" + String));
    this->x_devision_label->setText(QString::fromUtf8(" Цена деления Ox:"));
    this->y_devision_label->setText(QString::fromUtf8(" Цена деления Oy:"));
    this->grpixstep_label->setText(QString::fromUtf8(" Шаг сетки:"));

    this->x_devision = new QLineEdit();
    this->y_devision = new QLineEdit();
    this->grpixstep = new QLineEdit();
    x_devision->setStyleSheet(QString ("QLineEdit" + String));
    y_devision->setStyleSheet(QString ("QLineEdit" + String));
    grpixstep->setStyleSheet(QString ("QLineEdit" + String));
    this->x_devision->setMaximumHeight(17);
    this->y_devision->setMaximumHeight(17);
    this->grpixstep->setMaximumHeight(17);
    QObject::connect(this->x_devision, SIGNAL(textChanged(QString)),this,SLOT(x_devision_editingFinished(QString)));
    QObject::connect(this->y_devision, SIGNAL(textChanged(QString)),this,SLOT(y_devision_editingFinished(QString)));
    QObject::connect(this->grpixstep, SIGNAL(textChanged(QString)),this,SLOT(grpixstep_editingFinished(QString)));
    this->x_devision->setText(QString::number(x_div));
    this->y_devision->setText(QString::number(y_div));
    this->grpixstep->setText(QString::number(X_GridPixStep));

    //this->addWidget(this->x_devision_label);
    //this->addWidget(this->y_devision_label);
    //this->addWidget(this->grpixstep_label);

    //this->addWidget(this->x_devision);
    //this->addWidget(this->y_devision);
    //this->addWidget(this->grpixstep);

}

double myGraphScene::my_rand(int accuracy)
{
  double a = 0;
  a = (qrand() % int (qPow(10, accuracy) + 1))/qPow(10, accuracy);
  return a;
}

void myGraphScene::setGeometry(qreal w, qreal h)
{
    this->setSceneRect(-w/2,-h/2,w-5,h-5);

    if (y_AxesOffset < -this->height()/2){y_AxesOffset = -this->height()/2;}
    if (y_AxesOffset > this->height()/2){y_AxesOffset = this->height()/2;}

    if (x_AxesOffset < -this->width()/2){x_AxesOffset = -this->width()/2;}
    if (x_AxesOffset > this->width()/2){x_AxesOffset = this->width()/2;}

    OXY_Point.setX(x_AxesOffset);
    OXY_Point.setY(y_AxesOffset);

    this->x_devision_label->setGeometry(this->sceneRect().x()+5,this->sceneRect().y()-17+this->sceneRect().height(),145,17);
    this->x_devision->setGeometry(this->x_devision_label->geometry().x()+97,this->x_devision_label->geometry().y(),50,17);

    this->y_devision_label->setGeometry(this->x_devision->geometry().x()+60,this->x_devision_label->geometry().y(),145,17);
    this->y_devision->setGeometry(this->y_devision_label->geometry().x()+97,this->y_devision_label->geometry().y(),50,17);

    this->grpixstep_label->setGeometry(this->y_devision->geometry().x()+60,this->x_devision_label->geometry().y(),145,17);
    this->grpixstep->setGeometry(this->grpixstep_label->geometry().x()+97,this->grpixstep_label->geometry().y(),50,17);

    //this->y_div = (double)(this->height())/(double)GridPixStep;
    //this->y_devision->setText(QString::number(y_div));

    this->Y_GridPixStep = (double)(this->height())/10;
    //this->X_GridPixStep = (double)(this->width())/30;
    this->mygrid->setXGridPixStep(this->X_GridPixStep);
    this->mygrid->setYGridPixStep(this->Y_GridPixStep);

    mygrid->setHeight(this->height());
    mygrid->setWidth(this->width());
    mygrid->setOXYPoint(this->OXY_Point);

}

qreal myGraphScene::getXDevision(void)
{
    qreal result = 0;
    result = this->x_div;
    return result;
}
qreal myGraphScene::getYDevision(void)
{
    qreal result = 0;
    result = this->y_div;
    return result;
}
qreal myGraphScene::getXGridPixStep(void)
{
    qreal result = 0;
    result = this->X_GridPixStep;
    return result;
}
qreal myGraphScene::getYGridPixStep(void)
{
    qreal result = 0;
    result = this->Y_GridPixStep;
    return result;
}
void myGraphScene::x_devision_editingFinished(QString s)
{
    this->x_div = s.toDouble();;
    this->mygrid->setXDivision(this->x_div);
    if (this->x_div != 0)
    {
        emit this->update_polygon(this);
    }
}

void myGraphScene::y_devision_editingFinished(QString s)
{
    this->y_div = s.toDouble();
    this->mygrid->setYDivision(this->y_div);
    if (this->y_div != 0)
    {
        emit this->update_polygon(this);
    }
}

void myGraphScene::setX_AxesOffset(int offset)
{
    this->x_AxesOffset = offset;
    OXY_Point.setX(this->x_AxesOffset);
}
void myGraphScene::setY_AxesOffset(int offset)
{
    this->y_AxesOffset = offset;
    OXY_Point.setY(this->y_AxesOffset);
}
void myGraphScene::setOXYPoint(QPoint OXY_Point)
{
    this->OXY_Point = OXY_Point;
    this->x_AxesOffset = OXY_Point.x();
    this->y_AxesOffset = OXY_Point.y();
}
QPoint myGraphScene::getOXYPoint(void)
{
    return this->OXY_Point;
}

void myGraphScene::grpixstep_editingFinished(QString s)
{
    this->X_GridPixStep = s.toDouble();
    this->Y_GridPixStep = s.toDouble();

    if (this->X_GridPixStep != 0)
    {
        this->removeItem(mygrid);
        this->mygrid->setXGridPixStep(this->X_GridPixStep);
        this->mygrid->setYGridPixStep(this->Y_GridPixStep);
        this->addItem(mygrid);
        this->mygrid->setZValue(-100);
        emit this->update_polygon(this);
    }
}

void myGraphScene::setGrid(void)
{
    // сетка
    mygrid = new myGraphGrid();
    mygrid->setXGridPixStep(X_GridPixStep);
    mygrid->setYGridPixStep(Y_GridPixStep);
    this->addItem(mygrid);
}

void myGraphScene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    int delta = wheelEvent->delta()/120;
    if (x_devision->underMouse() == true)
    {
        this->x_div += delta*x_mult;
        if (this->x_div  < 0)
        {
            this->x_div = 0;
        }
        this->x_devision->setText(QString::number(x_div));
    }
    if (y_devision->underMouse() == true)
    {
        this->y_div += delta*y_mult;
        if (this->y_div  < 0)
        {
            this->y_div = 0;
        }
        this->y_devision->setText(QString::number(y_div));
    }
    if (grpixstep->underMouse() == true)
    {
        this->X_GridPixStep += delta*g_mult;
        this->Y_GridPixStep += delta*g_mult;
        if (this->X_GridPixStep < 1)
        {
            this->X_GridPixStep = 1;
            this->Y_GridPixStep = 1;
        }
        this->grpixstep->setText(QString::number(X_GridPixStep));
    }

}


/*
void myGraphScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    mouseEvent->buttons();
}
*/
