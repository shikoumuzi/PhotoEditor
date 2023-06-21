#ifndef __PAINTERWIDGET_H__
#define __PAINTERWIDGET_H__
#include<qwidget.h>
#include"../WorkSpace/workspace.h"
namespace PhotoEdit {
	class PainterWidget : public QWidget
	{
	public:
		friend class WorkSpace;
	public:
		PainterWidget(WorkSpace *parent):painter(this)
		{

		}
	public:
		QPainter painter;
	};
}

#endif // !__PAINTERWIDGET_H__
