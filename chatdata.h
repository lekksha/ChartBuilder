#ifndef CHARTDATA_H
#define CHARTDATA_H
#pragma once

#include <QString>
#include <QVector>

class ChartData
{
public:
    struct Point
    {
        QString key;
        QString value;
    };

    ChartData() = default;

    void addPoint(const Point& p);
    void setTitle(const QString& t);

private:
    QVector<Point> points;

    QString title;
};
#endif // CHARTDATA_H
