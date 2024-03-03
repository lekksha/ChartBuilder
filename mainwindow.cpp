#include <QSplitter>

#include "mainwindow.h"
#include "ioc.h"


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


    QObject::connect(files_view, &FilesView::fileSelected, this, &MainWindow::onFileSelected);
    QObject::connect(this, &MainWindow::fileReadSucceed, charts_view, &ChartsView::onFileReadSucceed);
    QObject::connect(this, &MainWindow::fileReadFailed, charts_view, &ChartsView::onFileReadFailed);
}

void MainWindow::onFileSelected(const QFileInfo& info)
{
    auto reader = IoCContainer::getService<IReader>();

    if (reader.get() == nullptr)
    {
        emit fileReadFailed("Failed to read file, now suitable reader.");
        return;
    }

    auto ret = reader->readFile(info.absoluteFilePath());

    if (ret.has_value())
        emit fileReadSucceed(ret.value());
    else
        emit fileReadFailed("Failed to read file, wrong data.");
}
