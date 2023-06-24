#include "ControlBaseBox.h"

namespace PhotoEdit
{
	struct ControlBaseBox::ControlBaseBoxData
	{
		WorkSpace* parent;
	};

	ControlBaseBox::ControlBaseBox(WorkSpace* parent, int minwsize, int minhsize):m_data(new ControlBaseBoxData)
	{
		this->m_data->parent = parent;

		// 设置大小
		this->setMinimumSize(minwsize, minhsize);
		this->setFixedSize(minwsize, minhsize);

		// 设置背景色
		QPalette pal(this->palette());
		//pal.setColor(QPalette::Background, qRgb(43, 43, 43));
		pal.setColor(QPalette::Background, qRgb(255, 255, 255));

		this->setAutoFillBackground(true);
		this->setPalette(pal);

	}

	ControlBaseBox::~ControlBaseBox()
	{
		delete this->m_data;
		this->m_data = nullptr;
	}

}
