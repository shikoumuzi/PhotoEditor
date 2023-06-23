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

namespace PhotoEdit
{
	struct WorkSpace::WorkSpaceData
	{
		PainterWidget* painter;
		
		ControlBaseBox* control_base_box;
		std::array<QWidget*, __WORKSPACE_FUNCTION_NUM__> control_box;

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
		this->m_data->control_base_box = new ControlBaseBox(minwsize, minhsize);

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
		QString qpath = QFileDialog::getExistingDirectory(this, "getExistingDirectory");
		this->m_data->image->imRead(qpath.toStdString());// 读取图像
		this->m_data->painter->begin(this->m_data->image->toQImage());// 加载图像到工作区
	}


}
