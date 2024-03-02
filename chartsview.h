#ifndef CHARTSVIEW_H
#define CHARTSVIEW_H

#pragma once

#include <QWidget>
#include <QPushButton>
#include <QtCharts/QtCharts>

#include "chartdata.h"

class ChartsView : public QWidget
{
    Q_OBJECT
public:
    ChartsView(QWidget* parent);

private slots:
    void onSaveClicked();

private:
    QChartView *chart_view;
    QPushButton *save_button;

    ChartData chart_data;
};

#endif // CHARTSVIEW_H


