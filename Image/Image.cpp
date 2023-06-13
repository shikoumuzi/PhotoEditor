#include"Image.h"
#include<boost/filesystem/path.hpp>
#include<qapplication.h>
#include<qdesktopwidget.h>
// eigen 声明要在cv2前面
#include <opencv2/core/eigen.hpp>
#include<opencv2/opencv.hpp>
namespace PhotoEdit {

	struct Image::ImageData 
	{
		//EMatrix m;
		cv::Mat m;
		QImage* p_qimage;
	};

	Image::Image():m_data(new struct ImageData)
	{
		this->m_data->p_qimage = nullptr;
	}
	Image::~Image()
	{
		if (this->m_data != nullptr)
		{
			if (this->m_data->p_qimage != nullptr)
			{
				delete this->m_data->p_qimage;
			}
			delete this->m_data;
		}
	}

	bool Image::imread(Path& path)
	{
		this->m_data->m = cv::Mat( cv::imread(path.string()));
		if (this->m_data->m.empty())
		{
			return false;
		}
		return true;
	}
	bool Image::imshow(String& windows_title)
	{
		if (this->m_data->m.empty()) 
		{
			return false;
		}
		QRect deskRect = QApplication::desktop()->availableGeometry();

		int w = deskRect.width();
		int h = deskRect.height();

		int ratio_h = (int)(this->m_data->m.cols / w) + 1;
		int ratio_w = (int)(this->m_data->m.rows / h) + 1;

		if (ratio_h > 1 || ratio_w > 1)
		{
			cv::namedWindow(windows_title.c_str(), 0);

			cv::resizeWindow(windows_title.c_str(), (int)(this->m_data->m.cols / (ratio_w + 1))/2 , (int)(this->m_data->m.cols / (ratio_h + 1))/2);
		}


		cv::imshow(windows_title.c_str(), this->m_data->m);
		cv::waitKey(0);
		return false;
	}
		


	QImage* Image::toQImage()
	{
		if (this->m_data->m.empty())
		{
			return nullptr;
		}
		if (this->m_data->p_qimage == nullptr)
		{
			this->m_data->p_qimage = new QImage(static_cast<const unsigned char*>(this->m_data->m.data), this->m_data->m.cols, this->m_data->m.rows, this->m_data->m.step, QImage::Format_RGB888);
			return this->m_data->p_qimage;
		}
		return this->m_data->p_qimage;
	}
	QPixmap* Image::toQPixmap()
	{
		if (this->m_data->m.empty())
		{
			return nullptr;
		}
		if (this->m_data->p_qimage != nullptr)
		{
			return new QPixmap(QPixmap::fromImage(*this->m_data->p_qimage));
		}
		else
		{
			return new QPixmap(QPixmap::fromImage(*this->toQImage()));
		}
	}
	cv::Mat* Image::toMat()
	{
		if (this->m_data->m.empty())
		{
			return nullptr;
		}
		return &this->m_data->m;
	}

	void Image::finalize(void* image)
	{
		if(image != &this->m_data->m)
			delete image;
	}


	void Image::synchronization()
	{
		if (this->m_data->p_qimage != nullptr)
		{
			QRgb* line = nullptr;
			for (int i = 0; i < this->m_data->m.rows; ++i)
			{
				line = (QRgb*)this->m_data->p_qimage->scanLine(i);
				for (int j = 0; j < this->m_data->m.cols; ++j)
				{
					
					this->m_data->p_qimage-> \
						setPixel(j, i, 
								qRgb(this->m_data->m.ptr<uchar>(i, j)[0],
												this->m_data->m.ptr<uchar>(i, j)[1],
												this->m_data->m.ptr<uchar>(i, j)[2]));
				}
			}
		}
	}
	void Image::cv2eigenC3(CMatrix& cm, EMatrix& em)
	{
		for (int i = 0; i < cm.rows; ++i)
		{
			for (int j = 0; j < cm.cols; ++j)
			{
				em(i, j)[0] = (double)(cm.ptr<uchar>(i, j))[0];
				em(i, j)[1] = (double)(cm.ptr<uchar>(i, j))[1];
				em(i, j)[2] = (double)(cm.ptr<uchar>(i, j))[2];
			}
		}
	}
	void Image::eigen2cvC3(EMatrix& em, CMatrix& cm)
	{
		for (int i = 0; i < cm.rows; ++i)
		{
			for (int j = 0; j < cm.cols; ++j)
			{
				cm.ptr<uchar>(i, j)[0] = (uchar)em(i, j)[0];
				cm.ptr<uchar>(i, j)[1] = (uchar)em(i, j)[1];
				cm.ptr<uchar>(i, j)[2] = (uchar)em(i, j)[2];
			}
		}
	}
	void Image::eigen2qimage(EMatrix& em, QImage& qm)
	{
		QRgb* line = nullptr;
		uchar r = 0, g = 0, b = 0;
		for (int y = 0; y < qm.height(); ++y)
		{
			line = reinterpret_cast<QRgb*>(qm.scanLine(y));
			EVector* rgb_vector = em.row(y).data();
			for (int x = 0; x < qm.width(); ++x)
			{
				QRgb& rgb = line[x];
				b = (uchar)(*rgb_vector->col(0).data() / 255);
				g = (uchar)(*rgb_vector->col(1).data() / 255);
				r = (uchar)(*rgb_vector->col(2).data() / 255);
				rgb = qRgba(qRed(r), qGreen(g), qBlue(b), qAlpha(rgb));
			}
		}
	}
	
}