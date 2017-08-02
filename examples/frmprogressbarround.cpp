#include "frmprogressbarround.h"
#include "ui_frmprogressbarround.h"
#include "progressbarround.h"
#include "flatui.h"

frmProgressBarRound::frmProgressBarRound(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmProgressBarRound)
{
	ui->setupUi(this);

    FlatUI::Instance()->setSliderQss(ui->slider, 8, "#505050", "#1ABC9C", "#1ABC9C");

	//默认样式+值格式+圆环颜色
	QPalette p1;
	p1.setColor(QPalette::Highlight, QColor(24, 189, 155));
	p1.setColor(QPalette::Text, QColor(24, 189, 155));
	p1.setColor(QPalette::Shadow, QColor(24, 189, 155));
    ui->roundBar1->setPalette(p1);
	ui->roundBar1->setFormat("%v");
    ui->roundBar1->setPrecision(0);
	ui->roundBar1->setNullPosition(0);
	connectToSlider(ui->roundBar1);

	//饼状图+背景色+起始位置
	QPalette p2;
	p2.setColor(QPalette::Base, QColor(97, 117, 118));
	p2.setColor(QPalette::Text, QColor(250, 250, 250));
	p2.setColor(QPalette::Highlight, QColor(255, 107, 107));
	p2.setColor(QPalette::Shadow, QColor(255, 107, 107));
    ui->roundBar2->setPalette(p2);
	ui->roundBar2->setNullPosition(ProgressBarRound::PositionRight);
	ui->roundBar2->setBarStyle(ProgressBarRound::BarStyle_Pie);
	connectToSlider(ui->roundBar2);

	//线状图+线颜色
	QPalette p3;
	p3.setColor(QPalette::Highlight, QColor(100, 184, 255));
    ui->roundBar3->setPalette(p3);
	ui->roundBar3->setBarStyle(ProgressBarRound::BarStyle_Line);
	ui->roundBar3->setOutlinePenWidth(5);
	ui->roundBar3->setDataPenWidth(5);
	connectToSlider(ui->roundBar3);

	//默认样式+自定义颜色组合
	QPalette p4;
	p4.setColor(QPalette::AlternateBase, QColor(240, 240, 240));
	p4.setColor(QPalette::Text, QColor(255, 107, 107));
	p4.setColor(QPalette::Highlight, QColor(255, 107, 107));
	p4.setColor(QPalette::Shadow, QColor(255, 107, 107));
    ui->roundBar4->setPalette(p4);
	ui->roundBar4->setNullPosition(ProgressBarRound::PositionLeft);
    ui->roundBar4->setPrecision(0);

	QGradientStops gradientPoints4;
	gradientPoints4 << QGradientStop(0, QColor(254, 64, 64)) << QGradientStop(0.5, QColor(255, 127, 36)) << QGradientStop(1, QColor(238, 238, 0));
    ui->roundBar4->setGradientData(gradientPoints4);
	connectToSlider(ui->roundBar4);

	//饼图样式+自定义颜色组合
	QPalette p5;
	p5.setColor(QPalette::Highlight, QColor(24, 189, 155));
	p5.setBrush(QPalette::Base, QColor(255, 107, 107));
	p5.setColor(QPalette::Text, QColor(250, 250, 250));
	p5.setColor(QPalette::Shadow, QColor(24, 189, 155));
    ui->roundBar5->setPalette(p5);
	ui->roundBar5->setNullPosition(ProgressBarRound::PositionLeft);
	ui->roundBar5->setBarStyle(ProgressBarRound::BarStyle_Pie);
	connectToSlider(ui->roundBar5);

	//线状样式+自定义边框宽度
    ui->roundBar6->setPalette(p3);
    ui->roundBar6->setPrecision(2);
	ui->roundBar6->setBarStyle(ProgressBarRound::BarStyle_Line);
	ui->roundBar6->setOutlinePenWidth(18);
	ui->roundBar6->setDataPenWidth(10);
	ui->roundBar6->setClockWise(false);
	connectToSlider(ui->roundBar6);
}

frmProgressBarRound::~frmProgressBarRound()
{
	delete ui;
}

void frmProgressBarRound::connectToSlider(ProgressBarRound *bar)
{
	bar->setRange(ui->slider->minimum(), ui->slider->maximum());
	bar->setValue(ui->slider->value());
	connect(ui->slider, SIGNAL(valueChanged(int)), bar, SLOT(setValue(int)));
}
