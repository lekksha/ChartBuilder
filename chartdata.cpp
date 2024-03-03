#include "chartdata.h"

void ChartData::addPoint(const Point& p)
{
    points.append(p);
}

void ChartData::setTitle(const QString& t)
{
    title = t;
}

void BarChart::update(QChart* chart, const ChartData& data)
{
    chart->removeAllSeries();
    for (auto axis : chart->axes())
        chart->removeAxis(axis);

    auto series = new QBarSeries();

    for (auto point : data.points)
    {
        auto ok = true;
        auto value = point.value.toFloat(&ok);

        if (ok)
        {
            auto barSet = new QBarSet(point.key);
            barSet->append(value);
            series->append(barSet);
        }
        else
            return;
    }

    auto valueAxis = new QValueAxis();

    chart->legend()->show();
    chart->addSeries(series);
    chart->addAxis(valueAxis, Qt::AlignLeft);

    series->attachAxis(valueAxis);
}

void PieChart::update(QChart* chart, const ChartData& data)
{

}
