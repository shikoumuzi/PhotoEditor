#include"Image.h"
#include<Eigen/Core>
#include<Eigen/Geometry>
#include<boost/filesystem/path.hpp>
namespace PhotoEdit {

	struct Image::ImageData {
		Eigen::MatrixXd m;
	};

	Image::Image()
	{
	}
	Image::~Image()
	{
	}

	bool Image::imread(Path path)
	{
		return false;
	}

	bool Image::imread(Path& path)
	{
		return false;
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