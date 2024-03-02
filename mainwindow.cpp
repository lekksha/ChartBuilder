#include <QSplitter>

#include "mainwindow.h"


MainWindow::MainWindow() :
    QMainWindow(nullptr)
{
    files_view = new FilesView(this);
    charts_view = new ChartsView(this);

    auto splitter = new QSplitter(this);
    splitter->addWidget(files_view);
    splitter->addWidget(charts_view);

    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 3);
    splitter->setHandleWidth(1);

    setCentralWidget(splitter);

    setMinimumHeight(450);
}
