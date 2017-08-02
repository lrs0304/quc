#include "frmnavprogressbar.h"
#include "ui_frmnavprogressbar.h"
#include "navprogressbar.h"
#include "qtimer.h"

frmNavProgressBar::frmNavProgressBar(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmNavProgressBar)
{
	ui->setupUi(this);
    QTimer::singleShot(0, this, SLOT(initForm()));
}

frmNavProgressBar::~frmNavProgressBar()
{
	delete ui;
}

void frmNavProgressBar::initForm()
{
	QStringList topInfo;
	QStringList bottomInfo;

	topInfo.clear();
    topInfo << "创建订单" << "审核订单" << "生产" << "配送" << "签收";

	ui->widget1->setTopInfo(topInfo);
	ui->widget1->setMaxStep(5);
	ui->widget1->setCurrentStep(3);

	ui->widget2->setTopInfo(topInfo);
	ui->widget2->setMaxStep(5);
	ui->widget2->setCurrentStep(5);

	topInfo.clear();
	topInfo << "拍下商品" << "付款到支付宝" << "卖家发货" << "确认收货" << "评价";

	bottomInfo.clear();
	bottomInfo << "2016-11-24 20:58:59" << "2016-11-24 21:25:26" << "2016-11-25 10:25:26" << "2016-11-25 15:26:58" << "2016-11-25 20:36:39";

	ui->widget3->setTopInfo(topInfo);
	ui->widget3->setBottomInfo(bottomInfo);
	ui->widget3->setMaxStep(5);
	ui->widget3->setCurrentStep(3);

	ui->widget4->setTopInfo(topInfo);
	ui->widget4->setBottomInfo(bottomInfo);
	ui->widget4->setMaxStep(5);
	ui->widget4->setCurrentStep(5);

	topInfo.clear();
	topInfo << "已发货" << "运输中" << "派件中" << "已签收" << "已评价";

	bottomInfo.clear();
	bottomInfo << "深圳市" << "上海市";

	ui->widget5->setTopInfo(topInfo);
	ui->widget5->setBottomInfo(bottomInfo);
	ui->widget5->setMaxStep(5);
	ui->widget5->setCurrentStep(3);

	ui->widget6->setTopInfo(topInfo);
	ui->widget6->setBottomInfo(bottomInfo);
	ui->widget6->setMaxStep(5);
	ui->widget6->setCurrentStep(5);
}
