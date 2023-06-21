#ifndef __WORKSPACE_H__
#define __WORKSPACE_H__

#include<qpainter.h>
#include<qbrush.h>
#include<qimage.h>
#include<qwidget.h>
#include"../PhotoEditor/PhotoEditor.h"
#include<boost/filesystem.hpp>


namespace PhotoEdit {

	class WorkSpace:public QWidget
	{
	public:
		using Path = boost::filesystem::path;
	public:
		struct WorkSpaceData;
	public:
		WorkSpace(PhotoEdit* parent);

	public: //界面初始化
		void initPainter();
		void initControlBoard();
		void initControlFrame();
	
	public:
		void replaceControlBoard();
		void addControlBoard();
		void deleteControlBoard();
	public:
		void readImage();
	private:
		WorkSpaceData* m_data;
	};

}
#endif // !__WORKSPACE_H__
