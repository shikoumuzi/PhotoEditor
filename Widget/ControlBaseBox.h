#ifndef __CONTROLBASEBOX_H__
#define __CONTROLBASEBOX_H__
#include"qwidget.h"
#include"../WorkSpace/workspace.h"
namespace PhotoEdit
{
	class ControlBaseBox: public QWidget
	{
	public:
		struct ControlBaseBoxData;
	public:
		ControlBaseBox(WorkSpace* parent, int minwsize, int minhsize);
		~ControlBaseBox();

	private:
		ControlBaseBoxData* m_data;
	};
}

#endif // !__CONTROLBASEBOX_H__
