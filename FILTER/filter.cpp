#include "filter.h"

Filter::Filter(unsigned int len, QObject *parent) : QObject(parent)
{
    buffer_length = len;
    current_index = 0;
}

void   Filter::add_value(double value)
{
    if (Buffer.length() < buffer_length)
    {
        Buffer.append(value);
        Summator += value;
        current_index++;
    }
    else
    {
        double val = Buffer.at(0);
        Buffer.removeAt(0);
        Buffer.append(value);
        Summator -= val;
        Summator += value;

    }
}
double Filter::get_result(void)
{
    return Summator/Buffer.length();
}

