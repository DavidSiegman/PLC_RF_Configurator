#include "mygraphscene.h"

myGraphScene::myGraphScene(QObject *parent) : QGraphicsScene(parent)
{
    this->setFocus();
    this->GridPixStep = 10;

    this->setGrid();

    this->x_div = 0.2;
    this->y_div = 12;

    x_mult = 0.01, y_mult = 0.01, g_mult = 1;

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
    this->grpixstep->setText(QString::number(GridPixStep));

    this->addWidget(this->x_devision_label);
    this->addWidget(this->y_devision_label);
    this->addWidget(this->grpixstep_label);

    this->addWidget(this->x_devision);
    this->addWidget(this->y_devision);
    this->addWidget(this->grpixstep);
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
    this->x_devision_label->setGeometry(this->sceneRect().x()+5,this->sceneRect().y()-17+this->sceneRect().height(),145,17);
    this->x_devision->setGeometry(this->x_devision_label->geometry().x()+97,this->x_devision_label->geometry().y(),50,17);

    this->y_devision_label->setGeometry(this->x_devision->geometry().x()+60,this->x_devision_label->geometry().y(),145,17);
    this->y_devision->setGeometry(this->y_devision_label->geometry().x()+97,this->y_devision_label->geometry().y(),50,17);

    this->grpixstep_label->setGeometry(this->y_devision->geometry().x()+60,this->x_devision_label->geometry().y(),145,17);
    this->grpixstep->setGeometry(this->grpixstep_label->geometry().x()+97,this->grpixstep_label->geometry().y(),50,17);
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
qreal myGraphScene::getGridPixStep(void)
{
    qreal result = 0;
    result = this->GridPixStep;
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

void myGraphScene::grpixstep_editingFinished(QString s)
{
    this->GridPixStep = s.toDouble();

    if (this->GridPixStep != 0)
    {
        this->removeItem(mygrid);
        this->mygrid->setGridPixStep(this->GridPixStep);
        this->addItem(mygrid);
        this->mygrid->setZValue(-100);
        emit this->update_polygon(this);
    }
}

void myGraphScene::setGrid(void)
{
    // сетка
    mygrid = new myGraphGrid();
    mygrid->setGridPixStep(GridPixStep);
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
        this->GridPixStep += delta*g_mult;
        if (this->GridPixStep < 1)
        {
            this->GridPixStep = 1;
        }
        this->grpixstep->setText(QString::number(GridPixStep));
    }

}
/*
void myGraphScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    mouseEvent->buttons();
}
*/
