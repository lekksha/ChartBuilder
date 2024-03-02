#include "chartsview.h"

ChartsView::ChartsView(QWidget* parent) :
    QWidget(parent)
{
    auto vbox_layout = new QVBoxLayout(this);

    save_button = new QPushButton();
    save_button->setText("Save To PDF");
    vbox_layout->addWidget(save_button, 0, Qt::AlignRight);

    chart_view = new QChartView();
    vbox_layout->addWidget(chart_view);

    setMinimumWidth(400);

    QObject::connect(save_button, &QPushButton::clicked, this, &ChartsView::onSaveClicked);
}

void ChartsView::onSaveClicked()
{
    auto filePath = QFileDialog::getSaveFileName(this, "Save as", QDir::currentPath(), "PDF (*.pdf)");

    if (filePath.isEmpty())
        return;

    auto pdfWriter = QPdfWriter(filePath);
    auto painter = QPainter(&pdfWriter);
    chart_view->render(&painter);
    painter.end();
}
