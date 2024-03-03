#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "chartsview.h"
#include "filesview.h"
#include "reader.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

signals:
    void fileReadSucceed(const ChartData& data);
    void fileReadFailed(const QString& error);

private slots:
    void onFileSelected(const QFileInfo& info);

private:
    // views
    FilesView *files_view{nullptr};
    ChartsView *charts_view{nullptr};
};
#endif // MAINWINDOW_H
