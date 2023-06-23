#ifndef __WORKSPACE_H__
#define __WORKSPACE_H__

#include<qpainter.h>
#include<qbrush.h>
#include<qimage.h>
#include<qwidget.h>
#include<boost/filesystem.hpp>
#include<qapplication.h>
namespace PhotoEdit {

#define __WORKSPACE_FUNCTION_NUM__ 4
	class WorkSpace:public QWidget
	{
	public:
		using Path = boost::filesystem::path;
	public:
		struct WorkSpaceData;
	public:
		WorkSpace();
		~WorkSpace();
	public: //�����ʼ��
		void initPainter(int minwsize, int minhsize);
		void initControlBoard(int minwsize, int minhsize);
		void initControlFrame();
	
	public:
		void replaceControlBoard();
		void addControlBoard();
		void deleteControlBoard();

	public:
		void resizeEvent(QResizeEvent* event);



	public:
		void readImage();
	private:
		WorkSpaceData* m_data;
	};

}
#endif // !__WORKSPACE_H__
