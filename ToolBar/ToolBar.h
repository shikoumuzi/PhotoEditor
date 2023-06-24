#ifndef __TOOLBAR_H__
#define __TOOLBAR_H__


#include<qmenubar.h>


namespace PhotoEdit
{
	class ToolBar :public QMenuBar
	{
		Q_OBJECT;
	public:
		struct ToolBarData;
	public:
		ToolBar(void* parent);
		~ToolBar();

	private:
		ToolBarData* m_data;
	};

}



#endif // !__TOOLBAR_H__
