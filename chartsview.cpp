#include "ioc.h"
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

    state_label = new QLabel();
    state_label->setText("Open File");
    vbox_layout->addWidget(state_label, 0, Qt::AlignCenter);

    chart_view->hide();
    state_label->show();

    setMinimumWidth(400);

    IoCContainer::registerService<IChart>(std::make_shared<BarChart>());

    QObject::connect(save_button, &QPushButton::clicked, this, &ChartsView::onSaveClicked);
}

void ChartsView::onFileReadFailed(const QString& error)
{
    state_label->setText(error);

    chart_view->hide();
    state_label->show();
}

void ChartsView::onFileReadSucceed(const ChartData& data)
{
    chart_data = data;

    auto chart = IoCContainer::getService<IChart>();
    chart->update(chart_view->chart(), chart_data);

    chart_view->show();
    state_label->hide();
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
