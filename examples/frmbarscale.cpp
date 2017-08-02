#include "frmbarscale.h"
#include "ui_frmbarscale.h"
#include "flatui.h"

frmBarScale::frmBarScale(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmBarScale)
{
    ui->setupUi(this);
    this->initForm();
}

frmBarScale::~frmBarScale()
{
    delete ui;
}

void frmBarScale::initForm()
{
    FlatUI::Instance()->setSliderQss(ui->verticalSlider1, 8, "#505050", "#1ABC9C", "#1ABC9C");
    FlatUI::Instance()->setSliderQss(ui->verticalSlider2, 8, "#505050", "#E74C3C", "#E74C3C");
    FlatUI::Instance()->setSliderQss(ui->verticalSlider3, 8, "#505050", "#31495A", "#31495A");

    ui->verticalSlider1->setRange(0, 800);
    connect(ui->verticalSlider1, SIGNAL(valueChanged(int)), ui->widget1, SLOT(setValue(int)));
    connect(ui->verticalSlider1, SIGNAL(valueChanged(int)), ui->widget2, SLOT(setValue(int)));

    ui->verticalSlider2->setRange(0, 100);
    connect(ui->verticalSlider2, SIGNAL(valueChanged(int)), ui->widget2, SLOT(setValueRight(int)));

    ui->verticalSlider1->setValue(300);
    ui->verticalSlider2->setValue(90);
}
