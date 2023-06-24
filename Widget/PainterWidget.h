#ifndef __PAINTERWIDGET_H__
#define __PAINTERWIDGET_H__
#include<qwidget.h>
#include"../WorkSpace/workspace.h"
namespace PhotoEdit {
	class PainterWidget : public QWidget
	{
	public:
		friend class WorkSpace;
		struct PainterWidgetData;
		using PaintSignal = void(*)(void*);
	public:
		PainterWidget(WorkSpace* parent, int minwsize, int minhsize);
		void begin(QPaintDevice* image);
		void binding(PaintSignal callback, void* data);
		void paintEvent(QPaintEvent* event) override;
	public:
		PainterWidgetData* m_data;
	};
}

#endif // !__PAINTERWIDGET_H__
