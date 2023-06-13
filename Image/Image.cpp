#include"Image.h"
#include<boost/filesystem/path.hpp>
#include<qapplication.h>
#include<qdesktopwidget.h>
// eigen 声明要在cv2前面
#include <opencv2/core/eigen.hpp>
#include<opencv2/opencv.hpp>
#include<qdebug.h>

namespace PhotoEdit {

	struct Image::ImageData 
	{
		//EMatrix m;
		cv::Mat m;
		QImage* p_qimage;
	};


	Image::Coordinates::Coordinates():parent(nullptr),row(-1),col(-1){}
	Image::Coordinates::Coordinates(Image* parent, int row, int col):parent(parent), row(row), col(col){}
	Image::Coordinates::~Coordinates()
	{
		this->parent = nullptr;
	}

	void Image::Coordinates::operator=(Coordinates& that)
	{
		this->row = that.row;
		this->col = that.col;
		this->parent = that.parent;
	}


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


	int Image::imread(Path& path)
	{
		this->m_data->m = cv::Mat( cv::imread(path.string()));
		if (this->m_data->m.empty())
		{
			qWarning("Image::imread: read failed");
			return MERROR::READ_FAILED;
		}
		return 0;
	}
	int Image::imshow(const String& windows_title)
	{
		return Image::imshow(this->m_data->m, windows_title);
	}
	int Image::imshow(const Image::CMatrix& cmatrix, const Image::String& windows_title)
	{
		if (cmatrix.empty())
		{
			qWarning("Image::imshow: matrix is empty, can not show");
			return MERROR::CMATRIX_EMPTY;
		}
		QRect deskRect = QApplication::desktop()->availableGeometry();

		int w = deskRect.width();
		int h = deskRect.height();

		int ratio_h = (int)(cmatrix.cols / w) + 1;
		int ratio_w = (int)(cmatrix.rows / h) + 1;

		if (ratio_h > 1 || ratio_w > 1)
		{
			cv::namedWindow(windows_title.c_str(), 0);

			cv::resizeWindow(windows_title.c_str(), (int)(cmatrix.cols / (ratio_w + 1)) / 2, (int)(cmatrix.cols / (ratio_h + 1)) / 2);
		}

		cv::imshow(windows_title.c_str(), cmatrix);
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
		if(image != &this->m_data->m && image != nullptr)
			delete image;
	}

	int Image::save(Path& path)
	{
		
		String extension = path.extension().string();
		if (extension == ".jpg" || extension == ".jepg" || extension == ".png" || extension == ".webp")
		{
			if (!cv::imwrite(path.string(), this->m_data->m))
			{
				qWarning("Image::save: cv::imwrite fail");
				return MERROR::SAVE_FAILED;
			}
		}
		else
		{
			qWarning("Image::save: error file extension");
			return MERROR::FILE_EXTENISON_ILLEGALITY;
		}
	}


	Image::CMatrix* Image::dilate(int& error_no, CMatrix& kernel, int iterator_times, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			
			return nullptr;
		}
		qDebug("%d, %d", Image::IMAGE_FLAG::DEFAULT, Image::IMAGE_FLAG::NEWOBJECT);
		CMatrix* ret_m = nullptr;
		switch (OPTION)
		{
		case IMAGE_FLAG::DEFAULT:
		{
			cv::dilate(this->m_data->m, this->m_data->m, kernel, cv::Point(-1, -1), iterator_times);
			ret_m = &this->m_data->m;
			break;
		}
		case IMAGE_FLAG::NEWOBJECT:
		{
			qDebug("new object");
			ret_m = new CMatrix;
			cv::dilate(this->m_data->m, *ret_m, kernel, cv::Point(-1, -1), iterator_times);
			break;
		}
		default:
			qWarning("Image::dilate: arg OPTION is undefined");
			error_no = MERROR::ERROR_ARG;
			return nullptr;
		}
		if (this->m_data->p_qimage != nullptr)
		{
			this->syncTotalQImage();
		}
		return ret_m;
	}
	Image::CMatrix* Image::dilate(int& error_no, CMatrix& kernel, Coordinates& start_co, Coordinates& end_co, int iterator_times,  int OPTION)
	{
		if (this != start_co.parent || this != end_co.parent)
		{
			qWarning("Image::dilate: Image is not compared");
			error_no = MERROR::IMAGE_NO_COMPARE;
			return nullptr;
		}
		int w = end_co.col - start_co.col;
		int h = end_co.row - start_co.row;

		CMatrix tmp_m;
		tmp_m.create(h, w, CV_8UC3);

		CMatrix partofm = this->m_data->m(cv::Rect(start_co.col, start_co.row, w, h));
		cv::dilate(partofm, tmp_m, kernel, cv::Point(-1, -1), iterator_times);
		tmp_m.copyTo(partofm);

		if (this->m_data->p_qimage != nullptr)
		{
			this->syncTotalQImage();
		}

		CMatrix* ret_m = nullptr;
		switch (OPTION)
		{
		case IMAGE_FLAG::DEFAULT:
			tmp_m.copyTo(partofm);
			ret_m = &this->m_data->m;
			break;
		case IMAGE_FLAG::NEWOBJECT:
			ret_m = new CMatrix;
			*ret_m = tmp_m;
			break;
		default:
			qWarning("Image::dilate: arg OPTION is undefined");
			error_no = MERROR::ERROR_ARG;
			return nullptr;
		}
		if (this->m_data->p_qimage != nullptr)
		{
			this->syncTotalQImage();
		}
		return ret_m;

	}


	Image::CMatrix* Image::erode(int& error_no, CMatrix& cm, int iterator_times, int OPTION)
	{
		return nullptr;
	}
	Image::CMatrix* Image::erode(int& error_no, CMatrix& kernel, Coordinates& start_co, Coordinates& end_co, int iterator_times, int OPTION)
	{
		return nullptr;
	}
	Image::CMatrix* Image::watershed(int& error_no, int value, int OPTION)
	{
		return nullptr;
	}
	Image::CMatrix* Image::watershed(int& error_no, int value, Coordinates& start_co, Coordinates& end_co, int OPTION)
	{
		return nullptr;
	}
	Image::CMatrix* Image::thresold(int& error_no, int value, int OPTION)
	{
		return nullptr;
	}
	Image::CMatrix* Image::thresold(int& error_no, int value, Coordinates& start_co, Coordinates& end_co, int OPTION)
	{
		return nullptr;
	}
	Image::CMatrix* Image::distanceTransform(int value, int OPTION)
	{
		return nullptr;
	}
	Image::CMatrix* Image::distanceTransform(int value, Coordinates& start_co, Coordinates& end_co, int OPTION)
	{
		return nullptr;
	}

	void Image::syncTotalQImage()
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

	void Image::syncPartQImage(Coordinates& start_co, Coordinates& end_co)
	{
	}

	void Image::syncTotalCMatrix()
	{
	}

	void Image::syncPartCMatrix(Coordinates& start_co, Coordinates& end_co)
	{
	}

	void Image::syncTotalQImageInThread()
	{
	}

	void Image::syncPartQImageInThread(Coordinates& start_co, Coordinates& end_co)
	{
	}

	void Image::syncTotalCMatrixInThread()
	{
	}

	void Image::syncPartCMatrixInThread(Coordinates& start_co, Coordinates& end_co)
	{
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

	void Image::eigen2qimageC3(EMatrix& em, QImage& qm)
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