#include"PainterWidget.h"
#include"qpalette.h"
#include"qrgba64.h"
namespace PhotoEdit
{
	struct PainterWidget::PainterWidgetData
	{
		WorkSpace* parent;
		QPainter painter;
		PaintSignal callback;
		void* data;
	};


	PainterWidget::PainterWidget(WorkSpace* parent, int minwsize, int minhsize):m_data(new PainterWidgetData)
	{
		this->m_data->callback = nullptr;
		this->m_data->data = nullptr;
		this->m_data->parent = parent;

		// 设置大小
		this->setMinimumSize(minwsize, minhsize);
		this->setFixedSize(minwsize, minhsize);

		// 设置透明度
		this->setWindowOpacity(0.3);
		
		// 设置背景色
		QPalette pal(this->palette());
		pal.setColor(QPalette::Background, qRgb(236, 236, 236));

		this->setAutoFillBackground(true);
		this->setPalette(pal);
		//this->setContentsMargins(10, 10, 10, 10);

	}
	void PainterWidget::begin(QPaintDevice* image)
	{
		this->m_data->painter.begin(image);
	}
	void PainterWidget::binding(PaintSignal callback, void* data)
	{
		this->m_data->callback = callback;
		this->m_data->data = data;
	}
	void PainterWidget::paintEvent(QPaintEvent* event)
	{


	}
}