#include"workspace.h"
#include"qpainter.h"
#include"../Image/Image.h"
#include"qdesktopwidget.h"
#include<qlayout.h>
#include<qfiledialog.h>
#include<qstring.h>
#include"../Widget/PainterWidget.h"
#include<array>
#include"qevent.h"
#include"../Widget/ControlBaseBox.h"
#include<qboxlayout.h>
#include"../ToolBar/ToolBar.h"
#include<qurl.h>
#include<string>
#include<vector>

namespace PhotoEdit
{
	struct WorkSpace::WorkSpaceData
	{
		PainterWidget* painter;
		ControlBaseBox* control_base_box;
		std::array<QWidget*, __WORKSPACE_FUNCTION_NUM__> control_box;

		std::string image_path;
		Image* image;

	};

	WorkSpace::WorkSpace():m_data(new WorkSpaceData)
	{

		this->m_data->image = new Image;
		auto desktop = QDesktopWidget();

		// 设置大小
		this->setMaximumSize(desktop.width(), desktop.height());
		this->setMinimumSize(1200, 800);
		this->setFixedSize(1200, 800);
		
		// 设置背景色
		QPalette pal(this->palette());
		pal.setColor(QPalette::Background, qRgb(37, 37, 38));
		this->setAutoFillBackground(true);
		this->setPalette(pal);


		// 设置内容
		// 总布局
		QHBoxLayout* total_layout = new QHBoxLayout();

		// 设置painter位置
		this->initPainter(900, 700);
		total_layout->addWidget(this->m_data->painter);

		total_layout->addStretch();
		// 设置控制台
		this->initControlBoard(200, 750);
		total_layout->addWidget(this->m_data->control_base_box);

		total_layout->setAlignment(Qt::AlignTop);
		this->setContentsMargins(40, 10, 10, 10);


		// 归总布局
		this->setLayout(total_layout);

	}

	WorkSpace::~WorkSpace()
	{
		for (QWidget*& x : this->m_data->control_box)
		{
			delete x;
			x = nullptr;
		}
		delete this->m_data->control_base_box;
		this->m_data->control_base_box = nullptr;

		delete this->m_data->image;
		this->m_data->image = nullptr;

		delete this->m_data->painter;
		this->m_data->painter = nullptr;

		delete this->m_data;
		this->m_data = nullptr;
	}

	void WorkSpace::initPainter(int minwsize, int minhsize)
	{
		this->m_data->image = new Image;
		this->m_data->painter = new PainterWidget(this, minwsize, minhsize);
	}

	void WorkSpace::initControlBoard(int minwsize, int minhsize)
	{
		this->m_data->control_base_box = new ControlBaseBox(this, minwsize, minhsize);

		for (QWidget*& x : this->m_data->control_box)
		{
			x = new QWidget;
			x->setMinimumSize(150, 750);
			x->setFixedSize(150, 750);
			x->hide();
		}

		
	}
	void WorkSpace::initControlFrame()
	{
	}
	void WorkSpace::replaceControlBoard()
	{
	}
	void WorkSpace::addControlBoard()
	{
	}
	void WorkSpace::deleteControlBoard()
	{
	}

	bool WorkSpace::isPathExit()
	{
		return !this->m_data->image_path.empty();
	}

	void WorkSpace::resizeEvent(QResizeEvent* event)
	{
		//QRect deskRect = QApplication::desktop()->availableGeometry();

		//QSize nowsize = this->size();

		//QSize newsize = event->size();

		//if (newsize.height() > deskRect.height())
		//{
		//	nowsize.setHeight(deskRect.height());
		//}
		//if (newsize.width() > deskRect.width())
		//{
		//	nowsize.setWidth(deskRect.width());
		//}
		//
		//this->resize(nowsize);
		//this->repaint();
		//this->adjustSize();
	}

	void WorkSpace::readImage()
	{
		QUrl fileUrl = QFileDialog::getOpenFileUrl(this, tr("Open Image"), QString(), "Images(*.png *.jpg)");
		QString fileName = fileUrl.toLocalFile();
		QFile file(fileName);
		if (!file.open(QFile::ReadOnly)) {
			qDebug("WorkSpace::readImage" + fileName.toUtf8() + ": Open Failed");
			return;
		}
		else {
			QByteArray ba = file.readAll();
			this->m_data->image->imRead(std::vector<char>(ba.begin(), ba.end())); // 使用 cv::imdecode 读取图片
		}
	}

	void WorkSpace::loadImage()
	{
		this->m_data->image->imRead(this->m_data->image_path, 0);

		qDebug("weight=%d, hight=%d", this->m_data->image->rows(), this->m_data->image->cols());

		
	}

	void WorkSpace::paintImage()
	{
		QImage* image = this->m_data->image->toQImage();

		//int w = 0, h = 0;
		//double w_dividend = 0.0, h_dividend = 0.0;
		//if (image->width() > this->width())
		//{
		//	w_dividend = (double)image->width() / this->width();

		//	if(w_dividend > 1)
		//		w = image->width() / w_dividend;
		//	else
		//	{
		//		h = image->height();
		//	}
		//}
		//if (image->height() > this->height())
		//{
		//	h_dividend = (double)image->width() / this->width();

		//	if (h_dividend > 1)
		//		h = this->height() / h_dividend;
		//	else
		//	{
		//		h = image->height();
		//	}
		//}
		//int radio = 0;
		//if (h_dividend > 1 || w_dividend > 1)
		//{
		//	radio = (h_dividend > w_dividend) ? h_dividend : w_dividend;
		//	h = this->height() / radio;
		//	w = this->width() / radio;
		//}
		//image->scaled(w, h);

		this->m_data->painter->begin(image);// 加载图像到工作区
	}

	



}
