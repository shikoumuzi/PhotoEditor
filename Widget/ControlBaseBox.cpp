#include "ControlBaseBox.h"

namespace PhotoEdit
{
	ControlBaseBox::ControlBaseBox(int minwsize, int minhsize)
	{
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
	}

}
