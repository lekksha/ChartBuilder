#include <QVBoxLayout>
#include <QFileDialog>

#include "ioc.h"
#include "reader.h"
#include "filesview.h"

FilesView::FilesView(QWidget* parent) :
    QWidget(parent)
{
    filesystem_model = new QFileSystemModel(this);
    list_view = new QListView(this);

    // TODO set filesystem filters

    filesystem_model->setRootPath(QDir::currentPath());

    list_view->setModel(filesystem_model);
    list_view->setRootIndex(filesystem_model->index(QDir::currentPath()));

    auto vbox_layout = new QVBoxLayout(this);

    auto hbox_layout = new QHBoxLayout(this);
    back_button = new QPushButton(this);
    back_button->setText("Back");
    change_directory_button = new QPushButton(this);
    change_directory_button->setText("Open");
    current_directory_line_edit = new QLineEdit(this);
    current_directory_line_edit->setText(QDir::currentPath());
    hbox_layout->addWidget(back_button, 0);
    hbox_layout->addWidget(current_directory_line_edit, 1);
    hbox_layout->addWidget(change_directory_button, 0);

    vbox_layout->addLayout(hbox_layout);
    vbox_layout->addWidget(list_view);

    setMinimumWidth(400);
    QObject::connect(list_view, &QListView::clicked, this, &FilesView::onFileClicked);
    QObject::connect(list_view, &QListView::activated, this, &FilesView::onFileSelected);
    QObject::connect(back_button, &QPushButton::clicked, this, &FilesView::onBackClicked);
    QObject::connect(change_directory_button, &QPushButton::clicked, this, &FilesView::onChangedDirectoryButton);
    QObject::connect(current_directory_line_edit, &QLineEdit::returnPressed, this, &FilesView::onChangedDirectoryLineEdit);
}

void FilesView::onFileClicked(const QModelIndex& index)
{
    auto extention = filesystem_model->fileInfo(index).fileName().split(".").last();

    if (extention == "csv")
    {
        IoCContainer::registerService<IReader>(std::make_shared<CSVReader>());
        return;
    }

    IoCContainer::registerService<IReader>(nullptr);
}

void FilesView::onBackClicked()
{
    auto directory_path = current_directory_line_edit->text();
    int start = directory_path.size() - 1;

    if (directory_path[start] == QChar('/') || directory_path[start - 1] == QChar('\\'))

        start--;

    while (start >= 0 && directory_path[start] != QChar('/') && directory_path[start] != QChar('\\'))
    {
        start--;
    }

    if (start < 0)
        return;

    directory_path.truncate(start+1);

    filesystem_model->setRootPath(directory_path);
    list_view->setRootIndex(filesystem_model->index(directory_path));
    current_directory_line_edit->setText(directory_path);
}

void FilesView::onChangedDirectoryButton()
{
    auto directory_path = QFileDialog::getExistingDirectory();

    if (!directory_path.isEmpty())
    {
        filesystem_model->setRootPath(directory_path);
        list_view->setRootIndex(filesystem_model->index(directory_path));
        current_directory_line_edit->setText(directory_path);
    }
}

void FilesView::onChangedDirectoryLineEdit()
{
    auto directory_path = current_directory_line_edit->text();
    QFileInfo dir{ directory_path };
    if (dir.isDir())
    {
        filesystem_model->setRootPath(directory_path);
        list_view->setRootIndex(filesystem_model->index(directory_path));
        current_directory_line_edit->setText(directory_path);
    }
}

void FilesView::onFileSelected(const QModelIndex& index)
{
    auto info = filesystem_model->fileInfo(index);
    if (info.isDir())
    {
        filesystem_model->setRootPath(info.absoluteFilePath());
        list_view->setRootIndex(index);
        current_directory_line_edit->setText(info.absoluteFilePath());
        return;
    }

    if (model_index != index)
    {
        emit FilesView::fileSelected(info);
        model_index = index;
    }
}
