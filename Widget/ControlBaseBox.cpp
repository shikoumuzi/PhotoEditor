#include "ControlBaseBox.h"

namespace PhotoEdit
{
	ControlBaseBox::ControlBaseBox(int minwsize, int minhsize)
	{
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
	}

}
