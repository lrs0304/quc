#include "frmsliderbar.h"
#include "ui_frmsliderbar.h"
#include "qtimer.h"
#include "sliderbar.h"
#include "qdebug.h"

frmSliderBar::frmSliderBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmSliderBar)
{
    ui->setupUi(this);
    this->initForm();
    QTimer::singleShot(100, this, SLOT(setIndex()));
}

frmSliderBar::~frmSliderBar()
{
    delete ui;
}

void frmSliderBar::initForm()
{
    QString item = "系统设置;教师管理;学生管理;数据查询;关于";

    ui->widget1->setBgRadius(5);
    ui->widget2->setBgRadius(5);

    ui->widget1->setBarRadius(5);
    ui->widget2->setBarRadius(5);

    ui->widget2->setBarColorStart(QColor(24, 189, 155));
    ui->widget2->setBarColorEnd(QColor(26, 188, 156));

    ui->widget4->setBarColorStart(QColor(24, 189, 155));
    ui->widget4->setBarColorEnd(QColor(26, 188, 156));

    ui->widget3->setLineWidth(3);
    ui->widget3->setBarStyle(SliderBar::BarStyle_Line_Top);

    ui->widget4->setLineWidth(3);
    ui->widget4->setBarStyle(SliderBar::BarStyle_Line_Top);

    ui->widget5->setLineWidth(4);
    ui->widget5->setLineColor(QColor(24, 189, 155));
    ui->widget5->setBarStyle(SliderBar::BarStyle_Line_Bottom);

    ui->widget6->setLineWidth(4);
    ui->widget6->setLineColor(QColor(24, 189, 155));
    ui->widget6->setBgColorStart(Qt::transparent);
    ui->widget6->setBgColorEnd(Qt::transparent);
    ui->widget6->setBarColorStart(Qt::transparent);
    ui->widget6->setBarColorEnd(Qt::transparent);
    ui->widget6->setTextNormalColor(QColor(50, 50, 50));
    ui->widget6->setTextSelectColor(QColor(255, 107, 107));
    ui->widget6->setBarStyle(SliderBar::BarStyle_Line_Bottom);

    ui->widget1->setItems(item);
    ui->widget2->setItems(item);
    ui->widget3->setItems(item);
    ui->widget4->setItems(item);
    ui->widget5->setItems(item);
    ui->widget6->setItems(item);
    ui->widgetLeft->setItems(item);

    ui->widgetLeft->setHorizontal(false);
    ui->widgetLeft->setBarStyle(SliderBar::BarStyle_Line_Left);

    ui->widgetLeft->setBarColorStart(QColor(13, 138, 166));
    ui->widgetLeft->setBarColorEnd(QColor(10, 134, 168));

    ui->widgetLeft->setBgColorStart(QColor(9, 52, 69));
    ui->widgetLeft->setBgColorEnd(QColor(13, 52, 69));

    ui->widgetLeft->setTextNormalColor(QColor(73, 138, 174));
    ui->widgetLeft->setTextSelectColor(QColor(223, 252, 253));

    ui->widgetLeft->setLineColor(QColor(223, 252, 253));
}

void frmSliderBar::setIndex()
{
    ui->widget1->setCurrentIndex(3);
    ui->widget2->setCurrentIndex(0);
    ui->widget3->setCurrentIndex(1);
    ui->widget4->setCurrentIndex(4);
    ui->widget5->setCurrentIndex(2);
    ui->widget6->setCurrentIndex(0);
    ui->widgetLeft->setCurrentIndex(1);
}
