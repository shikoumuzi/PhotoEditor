#include"Image.h"

namespace PhotoEdit {

	struct Image::ImageData {

	};

	Image::Image()
	{
	}

	Image::~Image()
	{
	}
	QImage* Image::toQImage()
	{
		return nullptr;
	}
	QPixmap* Image::toQPixmap()
	{
		return nullptr;
	}
	cv::Mat* Image::toMat()
	{
		return nullptr;
	}
	void Image::changePartOfImage()
	{
	}
}