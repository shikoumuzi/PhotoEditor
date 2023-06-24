#pragma execution_character_set("utf-8")
#include "ToolBar.h"
#include"../photoeditormainwindow.h"
#include<qaction.h>
namespace PhotoEdit
{
	struct ToolBar::ToolBarData
	{
		PhotoEditorMainWindow* parent;
	};


	ToolBar::ToolBar(void* parent) :m_data(new ToolBarData({ (PhotoEditorMainWindow*)parent }))
	{
		PhotoEditorMainWindow* main_parent = (PhotoEditorMainWindow*)parent;
		QMenu* menu1 = new QMenu("文件", main_parent );

		QAction* menu1_open = new QAction("打开", main_parent);
		menu1_open->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
		connect(menu1_open, &QAction::triggered, main_parent, &PhotoEditorMainWindow::readImage);
		menu1->addAction(menu1_open);

		this->addMenu(menu1);
	}

	ToolBar::~ToolBar()
	{
		delete this->m_data;
	}


}
