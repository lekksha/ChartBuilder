#ifndef FILESVIEW_H
#define FILESVIEW_H

#pragma once

#include <QWidget>
#include <QFileSystemModel>
#include <QListView>
#include <QPushButton>
#include <QLineEdit>

class FilesView : public QWidget
{
    Q_OBJECT
public:
    FilesView(QWidget* parent);

signals:
    void fileSelected(const QFileInfo& info);

private slots:
    void onFileSelected(const QModelIndex& index);
    void onBackClicked();
    void onChangedDirectoryButton();
    void onChangedDirectoryLineEdit();

private:
    QFileSystemModel *filesystem_model{nullptr};
    QListView *list_view{nullptr};

    QPushButton *back_button{nullptr};
    QPushButton *change_directory_button{nullptr};
    QLineEdit *current_directory_line_edit{nullptr};

    QModelIndex model_index;
};

#endif // FILESVIEW_H
