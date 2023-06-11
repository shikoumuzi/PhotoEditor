#ifndef __IMAGE_H__
#include<qpixmap.h>
#include<qimage>
#include<opencv2/core/core.hpp> 
#include<opencv2/highgui/highgui.hpp>   
#include<boost/filesystem/path.hpp>

namespace PhotoEdit {
	class Image
	{
	public:
		using Path = boost::filesystem::path;
	public: 
		struct ImageData;
	public:
		Image();
		~Image();

	public:
		bool imread(Path path);
		bool imread(Path& path);
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
