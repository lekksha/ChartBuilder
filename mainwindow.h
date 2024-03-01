#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "chartsview.h"
#include "filesview.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

private:
    // views
    FilesView *files_view{nullptr};
    ChartsView *charts_view{nullptr};
};
#endif // MAINWINDOW_H
