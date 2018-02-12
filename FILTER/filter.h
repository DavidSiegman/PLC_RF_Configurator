#ifndef FILTER_H
#define FILTER_H

#include <QObject>

class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(unsigned int len, QObject *parent = 0);
private:
    int           buffer_length;
    int           current_index;
    QList<double> Buffer;
    double        Summator;

signals:

public slots:
    void add_value(double value);
    double get_result(void);
};

#endif // FILTER_H
