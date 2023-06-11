#ifndef __IMAGE_H__
#include<qpixmap.h>
#include<qimage>
#include<opencv2/core/core.hpp> 
#include<opencv2/highgui/highgui.hpp>   
namespace PhotoEdit {
	class Image
	{
	public: 
		struct ImageData;
	public:
		Image();
		~Image();

	public:
		QImage* toQImage();
		QPixmap* toQPixmap();
		cv::Mat* toMat();
	public:
		void changePartOfImage();
	private:
		struct ImageData *m_data;
	};




}


#endif // !__IMAGE_H__
