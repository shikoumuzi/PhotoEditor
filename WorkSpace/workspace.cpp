#include"workspace.h"
#include"qpainter.h"
#include"../Image/Image.h"
#include"qdesktopwidget.h"
#include<qlayout.h>
#include<qfiledialog.h>
#include<qstring.h>
#include"../Widget/PainterWidget.h"
namespace PhotoEdit
{
	struct WorkSpace::WorkSpaceData
	{
		PainterWidget* painter;
		PhotoEdit* parent;

		Image* image;
	};

	WorkSpace::WorkSpace(PhotoEdit* parent)
	{
		this->m_data->parent = parent;

		// 设置窗口位置
		auto qr = this->frameGeometry();
		auto desktop = QDesktopWidget();
		auto cp = desktop.availableGeometry().center();
		qr.moveCenter(cp);

		// 设置大小
		this->setMaximumSize(desktop.width(), desktop.height());
		this->setMinimumSize(800, 600);
		this->setFixedSize(1200, 800);



		QHBoxLayout total_layout;

		QHBoxLayout painter_layout;

		// 设置painter位置
		this->initPainter();
		painter_layout.addWidget(this->m_data->painter);

	
	}
	void WorkSpace::initPainter()
	{
		this->m_data->image = new Image;
	}
	void WorkSpace::initControlBoard()
	{
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
	void WorkSpace::readImage()
	{
		QString qpath = QFileDialog::getExistingDirectory(this, "getExistingDirectory");
		this->m_data->image->imRead(qpath.toStdString());// 读取图像
		this->m_data->painter->begin(this->m_data->image->toQImage());// 加载图像到工作区
	}
}
