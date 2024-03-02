#include "chartdata.h"

void ChartData::addPoint(const Point& p)
{
    points.append(p);
}

void ChartData::setTitle(const QString& t)
{
    title = t;
}
