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

		// ���ô�С
		this->setMinimumSize(minwsize, minhsize);
		this->setFixedSize(minwsize, minhsize);

		// ���ñ���ɫ
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
