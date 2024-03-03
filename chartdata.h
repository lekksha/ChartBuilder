#ifndef CHARTDATA_H
#define CHARTDATA_H

#include <QString>
#include <QVector>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QtCharts>
#include <QtCharts/QChart>

class BarChart;
class PieChart;

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


    friend class BarChart;
    friend class PieChart;
};

class IChart
{
public:
    virtual ~IChart() = default;
    virtual void update(QChart* chart, const ChartData& data) = 0;
};

class BarChart : public IChart
{
public:
    void update(QChart* chart, const ChartData& data) override;
};

class PieChart : public IChart
{
public:
    void update(QChart* chart, const ChartData& data) override;
};
#endif // CHARTDATA_H
