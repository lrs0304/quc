#include "frmwaveplot.h"
#include "ui_frmwaveplot.h"
#include "flatui.h"
#include "qtimer.h"
#include "qdebug.h"

frmWavePlot::frmWavePlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmWavePlot)
{
    ui->setupUi(this);

    FlatUI::Instance()->setSliderQss(ui->horizontalSlider1, 8, "#505050", "#1ABC9C", "#1ABC9C");
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider2, 8, "#505050", "#E74C3C", "#E74C3C");
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider3, 8, "#505050", "#31495A", "#31495A");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start(5);

    ui->horizontalSlider1->setValue(5);
    ui->horizontalSlider2->setValue(20);
    ui->horizontalSlider3->setValue(100);
}

frmWavePlot::~frmWavePlot()
{
    delete ui;
}

void frmWavePlot::updateValue()
{
    ui->widgetPlot->clear();
}

void frmWavePlot::on_horizontalSlider1_valueChanged(int value)
{
    timer->setInterval(value);
}

void frmWavePlot::on_horizontalSlider2_valueChanged(int value)
{
    ui->widgetPlot->changeFlag1(value);
}

void frmWavePlot::on_horizontalSlider3_valueChanged(int value)
{
    ui->widgetPlot->changeFlag2(value);
}
