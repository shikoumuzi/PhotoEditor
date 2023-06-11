#include"Image.h"
#include<Eigen/Core>
#include<Eigen/Geometry>

namespace PhotoEdit {

	struct Image::ImageData {
		Eigen::MatrixXd m;
	};

	Image::Image()
	{
		this->m_data->m;
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