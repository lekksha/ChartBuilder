#ifndef CHARTSVIEW_H
#define CHARTSVIEW_H

#include <QWidget>
#include <QPushButton>

#include "chartdata.h"

class ChartsView : public QWidget
{
    Q_OBJECT
public:
    ChartsView(QWidget* parent);

public slots:
    void onFileReadSucceed(const ChartData& data);
    void onFileReadFailed(const QString& error);

private slots:
    void onSaveClicked();

private:
    QChartView *chart_view;
    QLabel *state_label;
    QPushButton *save_button;

    ChartData chart_data;
};

#endif // CHARTSVIEW_H


