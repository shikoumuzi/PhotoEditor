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




	Image::Image():m_data(new struct ImageData)
	{
		this->m_data->p_qimage = nullptr;
	}
	Image::Image(CMatrix& cm): Image()
	{
		if (!cm.empty()) {
			cm.copyTo(this->m_data->m);
		}
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


	int Image::imRead(const Path& path)
	{
		this->m_data->m = cv::Mat( cv::imread(path.string()));
		if (this->m_data->m.empty())
		{
			qWarning("Image::imread: read failed");
			return MERROR::READ_FAILED;
		}
		this->m_data->p_qimage = new QImage(static_cast<const unsigned char*>(this->m_data->m.data), this->m_data->m.cols, this->m_data->m.rows, this->m_data->m.step, QImage::Format_RGB888);
		return 0;
	}
	int Image::imShow(const String& windows_title)
	{
		return Image::imShow(this->m_data->m, windows_title);
	}
	int Image::imShowNoWait(const String& windows_title)
	{
		return Image::imShowNoWait(this->m_data->m, windows_title);
	}
	int Image::imShow(const QImage& image, const String& windows_title)
	{
		int ret = Image::imShowNoWait(image, windows_title);
		Image::waitkey();
		return ret;
	}
	int Image::imShowNoWait(const QImage& image, const String& windows_title)
	{
		switch (image.format())
		{
		case QImage::Format_RGB888:
			//qDebug("height=%d, width=%d, bits=%p, line=%d", image.height(), image.width(), (void*)image.constBits(), image.bytesPerLine());
			Image::imShowNoWait(Image::CMatrix(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine()), windows_title.c_str());
			break;
		case QImage::Format_Grayscale8:
			Image::imShowNoWait(Image::CMatrix(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine()), windows_title.c_str());
			break;
		default:
			qWarning("Image::imShowNoWait: image format is no matched");
			return MERROR::IMAGE_FORMAT_NO_MATCHED;
		}
		return 0;
	}
	int Image::imShow(const Image::CMatrix& cmatrix, const Image::String& windows_title)
	{
		int ret = Image::imShowNoWait(cmatrix, windows_title);
		Image::waitkey();
		return ret;
	}
	int Image::imShowNoWait(const CMatrix& cmatrix, const String& windows_title)
	{
		if (cmatrix.empty())
		{
			qWarning("Image::imShowNoWait: matrix is empty, can not show");
			return MERROR::CMATRIX_EMPTY;
		}
		if (windows_title.size() < 1)
		{
			qWarning("Image::imShowNoWait: windows title str length can not be less than 1");
			return MERROR::WINDOWS_TITLE_IS_TOO_SHORT;
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
		return 0;
	}
	inline void Image::waitkey()
	{
		cv::waitKey(0);
	}

	QImage* Image::toQImage()
	{
		if (this->m_data->m.empty())
		{
			qWarning("Image::toQImage: matrix is empty, can not show");
			return nullptr;
		}
		// 因为qimage在初始化时 同cv::mat使用同一块内存缓冲区，所以当类型相同时，cv的算法会直接作用在qimage上
		// 所以直接在imread初始化即可
		//if (this->m_data->p_qimage == nullptr)
		//{
		//	switch (this->m_data->m.type())
		//	{
		//	case CV_8UC3:
		//		this->m_data->p_qimage = new QImage(static_cast<const unsigned char*>(this->m_data->m.data), this->m_data->m.cols, this->m_data->m.rows, this->m_data->m.step, QImage::Format_RGB888);
		//		break;
		//	case CV_8UC1:
		//		this->m_data->p_qimage = new QImage(static_cast<const unsigned char*>(this->m_data->m.data), this->m_data->m.cols, this->m_data->m.rows, this->m_data->m.step, QImage::Format_Grayscale8);
		//		break;
		//	default:
		//		qWarning("Image::toQImage: image format is no matched");
		//		break;
		//	}
		//	return this->m_data->p_qimage;
		//}
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

	bool Image::isempty()
	{
		return this->m_data->m.empty();
	}
	int Image::rows()
	{
		return this->m_data->m.rows;
	}
	int Image::cols()
	{
		return this->m_data->m.cols;
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

	int Image::copyTo(Image& image)
	{
		this->m_data->m.copyTo(image.m_data->m);
		return 0;
	}


	Image* Image::Rgb2Gray(int& error_no, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}
		if (this->m_data->m.type() == CV_8UC1)
		{
			error_no = MERROR::IMAGE_FORMAT_NO_MATCHED;
			return nullptr;
		}

		CMatrix* ret_m = this->createObject(error_no, OPTION);

		if (ret_m != nullptr)
		{
			cv::cvtColor(this->m_data->m, *ret_m, cv::COLOR_BGR2GRAY);
			if (OPTION == IMAGE_FLAG::DEFAULT)
			{
				this->syncTotalQImage();
			}
		}

		return this->returnResult(ret_m);
	}

	Image* Image::dilate(int& error_no, CMatrix& kernel, int iterator_times, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}

		CMatrix* ret_m = this->createObject(error_no, OPTION);

		if (ret_m != nullptr)
		{
			cv::dilate(this->m_data->m, *ret_m, kernel, cv::Point(-1, -1), iterator_times);
			if (OPTION == IMAGE_FLAG::DEFAULT)
			{
				this->syncTotalQImage();
			}
		}

		return this->returnResult(ret_m);
	}
	Image* Image::dilate(int& error_no, CMatrix& kernel, const Coordinates& start_co, const Coordinates& end_co, int iterator_times,  int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}
		if ((error_no = this->checkCoordinates(start_co, end_co)) != 0)
		{
			return nullptr;
		}
		CMatrixPair ret_m = this->createPartObject(error_no, start_co, end_co, OPTION);
		if (ret_m.part_dst != nullptr)
		{
			cv::dilate(*ret_m.src, *ret_m.part_dst, kernel, cv::Point(-1, -1), iterator_times);
			if (OPTION == IMAGE_FLAG::DEFAULT)
			{
				this->syncPartQImage(start_co, end_co);
			}
		}
		else
		{
			error_no = MERROR::GET_IMAGE_BLOCK_FAILED;
			return nullptr;
		}
		return this->returnResult(ret_m);

	}

	Image* Image::erode(int& error_no, CMatrix& kernel, int iterator_times, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}

		CMatrix* ret_m = this->createObject(error_no, OPTION);
		if (ret_m != nullptr)
		{
			cv::erode(this->m_data->m, *ret_m, kernel, cv::Point(-1, -1), iterator_times);
			if (OPTION == IMAGE_FLAG::DEFAULT)
			{
				this->syncTotalQImage();
			}
		}
		return this->returnResult(ret_m);
	}
	Image* Image::erode(int& error_no, CMatrix& kernel, const Coordinates& start_co, const Coordinates& end_co, int iterator_times, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}
		if ((error_no = this->checkCoordinates(start_co, end_co)) != 0)
		{
			return nullptr;
		}
		CMatrixPair ret_m = this->createPartObject(error_no, start_co, end_co, OPTION);
		if (ret_m.part_dst != nullptr)
		{
			cv::erode(*ret_m.src, *ret_m.part_dst, kernel, cv::Point(-1, -1), iterator_times);
			if (OPTION == IMAGE_FLAG::DEFAULT)
			{
				this->syncPartQImage(start_co, end_co);
			}
		}
		else
		{
			error_no = MERROR::GET_IMAGE_BLOCK_FAILED;
			return nullptr;
		}

		return this->returnResult(ret_m);
	}

	Image* Image::watershed(int& error_no, int value, int OPTION)
	{
		return nullptr;
	}
	Image* Image::watershed(int& error_no, int value, const Coordinates& start_co, const Coordinates& end_co, int OPTION)
	{
		return nullptr;
	}

	Image* Image::thresold(int& error_no, int value, int max, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}

		CMatrix* ret_m = this->createObject(error_no, OPTION);
		if (ret_m != nullptr)
		{
			cv::threshold(this->m_data->m, *ret_m, value, max, cv::THRESH_BINARY);
			if (OPTION == IMAGE_FLAG::DEFAULT)
			{
				this->syncTotalQImage();
			}
		}
		return this->returnResult(ret_m);
	}
	Image* Image::thresold(int& error_no, int value,const Coordinates& start_co, const Coordinates& end_co, int max, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}
		if ((error_no = this->checkCoordinates(start_co, end_co)) != 0)
		{
			return nullptr;
		}
		CMatrixPair ret_m = this->createPartObject(error_no, start_co, end_co, OPTION);
		if (ret_m.part_dst != nullptr && ret_m.src != nullptr)
		{
			cv::threshold(*ret_m.src, *ret_m.part_dst, value, max, cv::THRESH_BINARY);
			if (OPTION == IMAGE_FLAG::DEFAULT)
			{
				this->syncPartQImage(start_co, end_co);
			}
		}
		else
		{
			error_no = MERROR::GET_IMAGE_BLOCK_FAILED;
			return nullptr;
		}

		return this->returnResult(ret_m);
	}

	Image* Image::distanceTransform(int& error_no, int value, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}

		if (this->m_data->m.type() != CV_8UC1)
		{
			error_no = MERROR::IMAGE_FORMAT_NO_MATCHED;
			return nullptr;
		}

		CMatrix* ret_m = this->createObject(error_no, OPTION);
		if (ret_m != nullptr)
		{
			int type = ret_m->type();
			cv::distanceTransform(this->m_data->m, *ret_m, cv::DIST_L1, 5);
			cv::threshold(*ret_m, *ret_m, value, 255, cv::THRESH_BINARY);

			ret_m->convertTo(*ret_m, type);
			if (OPTION == IMAGE_FLAG::DEFAULT)
			{
				this->syncTotalQImage();
			}
		}
		return this->returnResult(ret_m);
	}
	Image* Image::distanceTransform(int& error_no, int value, const Coordinates& start_co, const Coordinates& end_co, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}
		if ((error_no = this->checkCoordinates(start_co, end_co)) != 0)
		{
			return nullptr;
		}
		return nullptr;
	}

	Image* Image::add(int& error_no, Image& cm, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}
		if (this->m_data->m.rows != cm.rows() || this->m_data->m.cols != cm.cols())
		{
			error_no = MERROR::IMAGE_NO_COMPARE;
			return nullptr;
		}
		
		return nullptr;
	}

	Image* Image::sub(int& error_no, Image&, int OPTION)
	{
		return nullptr;
	}

	Image* Image::mut(int& error_no, Image&, int OPTION)
	{
		return nullptr;
	}

	Image* Image::divide(int& error_no, Image&, int OPTION)
	{
		return nullptr;
	}

	Image* Image::T()
	{
		return nullptr;
	}

	Image& Image::rotateLeft()
	{
		// TODO: 在此处插入 return 语句
		return *this;
	}

	Image& Image::rotateRight()
	{
		// TODO: 在此处插入 return 语句
		return *this;
	}

	Image* Image::offsetAll(int& error_no, int offsetvalue, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}
		CMatrix* ret_m = createObject(error_no, OPTION);
		int cv_bytesline = ret_m->step; // 获取每一行长度
		uchar* cv_data = ret_m->data;// 数据
		int p_row = 0;
		int point = 0;
		for (int i = 0; i < this->m_data->m.rows; ++i)
		{
			p_row = i * cv_bytesline;
			for (int j = 0; j < cv_bytesline; ++j)
			{
				point = cv_data[p_row + j] + offsetvalue;
				if (point < 0)
					cv_data[p_row + j] = 0;
				else if (point > 255)
					cv_data[p_row + j] = 255;
				else
					cv_data[p_row + j] = point;
			}
		}
		return this->returnResult(ret_m);
	}

	Image* Image::offsetAll(int& error_no, int offsetvalue, const Coordinates& start_co, const Coordinates& end_co, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}
		if ((error_no = this->checkCoordinates(start_co, end_co)) != 0)
		{
			return nullptr;
		}


		CMatrixPair ret_m = createPartObject(error_no,start_co, end_co, OPTION);
		int cv_bytesline = ret_m.part_dst->step; // 获取每一行长度
		uchar* cv_data = ret_m.part_dst->data;// 数据
		int p_row = 0;
		int point = 0;
		int end = end_co.col * 3;
		for (int i = start_co.row; i < end_co.row; ++i)
		{
			p_row = i * cv_bytesline;
			for (int j = start_co.col * 3; j < end; ++j)
			{
				point = cv_data[p_row + j] + offsetvalue;
				if (point < 0)
					cv_data[p_row + j] = 0;
				else if (point > 255)
					cv_data[p_row + j] = 255;
				else
					cv_data[p_row + j] = point;
			}
		}
		return this->returnResult(ret_m);
	}

	Image* Image::offsetR(int& error_no, int offsetvalue, int OPTION)
	{
		return this->offset(error_no, offsetvalue, IMAGE_COLOR::RED,
			Coordinates(this, 0, 0), Coordinates(this, this->m_data->m.rows, this->m_data->m.step), OPTION);
	}
	Image* Image::offsetR(int& error_no, int offsetvalue, const Coordinates& start_co, const Coordinates& end_co, int OPTION)
	{
		return this->offset(error_no, offsetvalue, IMAGE_COLOR::RED, Coordinates(this, start_co.row, start_co.col * 3), Coordinates(this, end_co.row, end_co.col * 3), true, OPTION);
	}

	Image* Image::offsetG(int& error_no, int offsetvalue, int OPTION)
	{
		return this->offset(error_no, offsetvalue, IMAGE_COLOR::GREEN,
			Coordinates(this, 0, 0), Coordinates(this, this->m_data->m.rows, this->m_data->m.step));
	}
	Image* Image::offsetG(int& error_no, int offsetvalue, const Coordinates& start_co, const Coordinates& end_co, int OPTION)
	{
		return this->offset(error_no, offsetvalue, IMAGE_COLOR::GREEN, Coordinates(this, start_co.row, start_co.col * 3), Coordinates(this, end_co.row, end_co.col * 3), true, OPTION);
	}

	Image* Image::offsetB(int& error_no, int offsetvalue, int OPTION)
	{
		return this->offset(error_no, offsetvalue, IMAGE_COLOR::BLUE, 
			Coordinates(this, 0, 0), Coordinates(this, this->m_data->m.rows, this->m_data->m.step));
	}
	Image* Image::offsetB(int& error_no, int offsetvalue, const Coordinates& start_co, const Coordinates& end_co, int OPTION)
	{
		return this->offset(error_no, offsetvalue, IMAGE_COLOR::BLUE, Coordinates(this, start_co.row, start_co.col * 3), Coordinates(this, end_co.row, end_co.col * 3), true, OPTION);

	}

	Image* Image::offset(int& error_no, int offsetvalue, int COLOR, const Coordinates& start_co, const Coordinates& end_co, bool is_part, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}
		if (this->m_data->m.type() == CV_8UC3)
		{
			if ((error_no = this->checkCoordinates(start_co, end_co)) != 0)
			{
				return nullptr;
			}
			if (COLOR == IMAGE_COLOR::BLUE)
			{
				COLOR = 0;
			}
			else if (COLOR == IMAGE_COLOR::GREEN)
			{
				COLOR = 1;
			}
			else if (COLOR == IMAGE_COLOR::RED)
			{
				COLOR = 2;
			}
			else
			{
				error_no = MERROR::ERROR_ARG;
				qWarning("Image::offset: arg COLOR is error");
				return nullptr;
			}

			CMatrix* ret_m = nullptr; 
			CMatrixPair ret_mp;
			if (!is_part)
			{
				ret_m = createObject(error_no, OPTION);
			}
			else
			{
				ret_mp = createPartObject(error_no, start_co, end_co, OPTION);
				ret_m = ret_mp.part_dst;
			}

			int cv_bytesline = ret_m->step; // 获取每一行长度
			uchar* cv_data = ret_m->data;// 数据
			int p_row = 0;
			int point = 0;

			for (int i = start_co.row; i < end_co.row; ++i)
			{
				p_row = i * cv_bytesline;
				for (int j = start_co.col; j < end_co.col; j += 3)
				{
					point = cv_data[p_row + j] + offsetvalue;
					if (point < 0)
						cv_data[p_row + j + COLOR] = 0;
					else if (point > 255)
						cv_data[p_row + j + COLOR] = 255;
					else
						cv_data[p_row + j + COLOR] = point;
				}
			}
			if (!is_part)
			{
				return this->returnResult(ret_m);
			}
			else
			{
				return this->returnResult(ret_mp);
			}
		}
		else
		{
			return this->offsetAll(error_no, offsetvalue,Coordinates(this, start_co.row, start_co.col / 3), Coordinates(this, end_co.row, end_co.col / 3), OPTION);
		}
	}

	Image* Image::offsetRGB(int& error_no, int RGB_BIT, int offsetvalue_r, int offsetvalue_g, int offsetvalue_b, int OPTION )
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}

		if ((RGB_BIT & IMAGE_COLOR::RED) == 0)
		{
			offsetvalue_r = 0;
		}
		if ((RGB_BIT & IMAGE_COLOR::GREEN) == 0)
		{
			offsetvalue_g = 0;
		}
		if ((RGB_BIT & IMAGE_COLOR::BLUE) == 0)
		{
			offsetvalue_b = 0;
		}

		CMatrix* ret_m = createObject(error_no, OPTION);
		int cv_bytesline = ret_m->step; // 获取每一行长度
		uchar* cv_data = ret_m->data;// 数据
		int p_row = 0;
		int point_r = 0;
		int point_g = 0;
		int point_b = 0;

		for (int i = 0; i < this->m_data->m.rows; ++i)
		{
			p_row = i * cv_bytesline;
			for (int j = 0; j < cv_bytesline; j += 3)
			{
				if (offsetvalue_b != 0)
				{
					point_r = cv_data[p_row + j + 2] + offsetvalue_r;
					if (point_r < 0)
						cv_data[p_row + j + 2] = 0;
					else if (point_r > 255)
						cv_data[p_row + j + 2] = 255;
					else
						cv_data[p_row + j + 2] = point_r;
				}
				if (offsetvalue_g != 0)
				{
					point_g = cv_data[p_row + j + 1] + offsetvalue_g;
					if (point_g < 0)
						cv_data[p_row + j + 1] = 0;
					else if (point_g > 255)
						cv_data[p_row + j + 1] = 255;
					else
						cv_data[p_row + j + 1] = point_g;
				}
				if (offsetvalue_b != 0)
				{
					point_b = cv_data[p_row + j] + offsetvalue_b;
					if (point_b < 0)
						cv_data[p_row + j] = 0;
					else if (point_b > 255)
						cv_data[p_row + j] = 255;
					else
						cv_data[p_row + j] = point_b;
				}
			}
		}
		return this->returnResult(ret_m);
	}
	Image* Image::offsetRGB(int& error_no, int RGB_BIT, int offsetvalue_r, int offsetvalue_g, int offsetvalue_b, const Coordinates& start_co, const Coordinates& end_co, int OPTION)
	{
		if (this->m_data->m.empty())
		{
			error_no = MERROR::CMATRIX_EMPTY;
			return nullptr;
		}

		if ((RGB_BIT & IMAGE_COLOR::RED) == 0)
		{
			offsetvalue_r = 0;
		}
		if ((RGB_BIT & IMAGE_COLOR::GREEN) == 0)
		{
			offsetvalue_g = 0;
		}
		if ((RGB_BIT & IMAGE_COLOR::BLUE) == 0)
		{
			offsetvalue_b = 0;
		}

		CMatrix* ret_m = createObject(error_no, OPTION);
		int cv_bytesline = ret_m->step; // 获取每一行长度
		uchar* cv_data = ret_m->data;// 数据
		int p_row = 0;
		int point_r = 0;
		int point_g = 0;
		int point_b = 0;

		for (int i = 0; i < this->m_data->m.rows; ++i)
		{
			p_row = i * cv_bytesline;
			for (int j = 0; j < cv_bytesline; j += 3)
			{
				if (offsetvalue_b != 0)
				{
					point_r = cv_data[p_row + j + 2] + offsetvalue_r;
					if (point_r < 0)
						cv_data[p_row + j + 2] = 0;
					else if (point_r > 255)
						cv_data[p_row + j + 2] = 255;
					else
						cv_data[p_row + j + 2] = point_r;
				}
				if (offsetvalue_g != 0)
				{
					point_g = cv_data[p_row + j + 1] + offsetvalue_g;
					if (point_g < 0)
						cv_data[p_row + j + 1] = 0;
					else if (point_g > 255)
						cv_data[p_row + j + 1] = 255;
					else
						cv_data[p_row + j + 1] = point_g;
				}
				if (offsetvalue_b != 0)
				{
					point_b = cv_data[p_row + j] + offsetvalue_b;
					if (point_b < 0)
						cv_data[p_row + j] = 0;
					else if (point_b > 255)
						cv_data[p_row + j] = 255;
					else
						cv_data[p_row + j] = point_b;
				}
			}
		}
		return this->returnResult(ret_m);
	}


	Image::CMatrix* Image::createObject(int& error_no, int OPTION)
	{
		CMatrix* ret_m = nullptr;
		switch (OPTION)
		{
		case IMAGE_FLAG::DEFAULT:
		{
			ret_m = &this->m_data->m;
			break;
		}
		case IMAGE_FLAG::NEWOBJECT:
		{
			ret_m = new CMatrix;
			this->m_data->m.copyTo(*ret_m);
			break;
		}
		default:
			qWarning("Image::dilate: arg OPTION is undefined");
			error_no = MERROR::ERROR_ARG;
			return nullptr;
		}
		return ret_m;
	}
	Image::CMatrixPair Image::createPartObject(int& error_no, const Coordinates& start_co, const Coordinates& end_co, int OPTION)
	{
		int w = end_co.col - start_co.col;
		int h = end_co.row - start_co.row;
		CMatrix* ret_part_dst = new CMatrix;
		CMatrix* ret_src = new CMatrix();

		switch (OPTION)
		{
		case IMAGE_FLAG::DEFAULT:
		{
			*ret_part_dst = this->m_data->m(cv::Rect(start_co.col, start_co.row, w, h));
			*ret_src = this->m_data->m(cv::Rect(start_co.col, start_co.row, w, h)); 
			return CMatrixPair({ ret_src , &this->m_data->m , ret_part_dst });
			break;
		}
		case IMAGE_FLAG::NEWOBJECT:
		{
			CMatrix* ret_total_dst = new CMatrix;
			this->m_data->m.copyTo(*ret_total_dst);

			*ret_part_dst = ret_total_dst->operator()(cv::Rect(start_co.col, start_co.row, w, h));


			*ret_src = this->m_data->m(cv::Rect(start_co.col, start_co.row, w, h));
			return CMatrixPair({ ret_src , ret_total_dst, ret_part_dst });
			break;
		}
		default:
			qWarning("Image::dilate: arg OPTION is undefined");
			error_no = MERROR::ERROR_ARG;
			delete ret_part_dst;
			ret_part_dst = nullptr;
			return CMatrixPair({ nullptr, nullptr, nullptr});
		}
	}

	int Image::checkCoordinates(const Coordinates& start_co, const Coordinates& end_co)
	{
		if (start_co.parent != end_co.parent || start_co.parent != this || end_co.parent != this)
		{
			qWarning("Image::checkCoordinates: coordinate is not belong to image");
			return MERROR::COORDINATE_NO_BELONG_TO_IMAGE;
		}
		if (start_co.row >= end_co.row || start_co.col >= end_co.col)
		{
			qWarning("Image::checkCoordinates: coordinate's value is error");
			return MERROR::COORDINATE_VALUE_ERROR;
		}
		return 0;
	}

	Image* Image::returnResult(CMatrix* cm)
	{
		Image* ret_img = new Image(*cm);
		if (cm != &this->m_data->m) {
			delete cm;
		}
		return ret_img;
	}
	Image* Image::returnResult(CMatrixPair& cm)
	{
		Image* ret_image = new Image(*cm.total_dst);
		if (cm.src != cm.total_dst)
		{
			if (cm.src != &this->m_data->m && cm.src != nullptr && cm.part_dst)
			{
				delete cm.src;
				cm.src = nullptr;
			}
			if (cm.total_dst != &this->m_data->m && cm.total_dst != nullptr)
			{
				delete cm.total_dst;
				cm.total_dst = nullptr;
			}
			if (cm.part_dst != &this->m_data->m && cm.part_dst != nullptr)
			{
				delete cm.part_dst;
				cm.part_dst = nullptr;
			}
		}
		else
		{
			if (cm.src != &this->m_data->m && cm.src != nullptr && cm.part_dst)
			{
				delete cm.src;
				cm.src = nullptr;
				cm.total_dst = nullptr;
			}
			if (cm.part_dst != &this->m_data->m && cm.part_dst != nullptr)
			{
				delete cm.part_dst;
				cm.part_dst = nullptr;
			}
		}
		return ret_image;
	}

	void Image::syncTotalQImage()
	{
		if (this->m_data->p_qimage != nullptr)
		{
			if (this->m_data->m.type() == CV_8UC3)
			{
				*this->m_data->p_qimage = QImage(static_cast<const unsigned char*>(this->m_data->m.data), this->m_data->m.cols, this->m_data->m.rows, this->m_data->m.step, QImage::Format_RGB888);
			}
			else if (this->m_data->m.type() == CV_8UC1)
			{
				*this->m_data->p_qimage = QImage(static_cast<const unsigned char*>(this->m_data->m.data), this->m_data->m.cols, this->m_data->m.rows, this->m_data->m.step, QImage::Format_Grayscale8);
			}
			else
			{
				qWarning("Image::syncTotalQImage: image format is not matched, type is %d", this->m_data->m.type());
			}
		}
	}
	void Image::syncPartQImage(const Coordinates& start_co, const Coordinates& end_co)
	{
		if (this->m_data->p_qimage != nullptr)
		{
			switch (this->m_data->m.type())
			{
			case CV_8UC3:
			{
				if (this->m_data->p_qimage->format() != QImage::Format_RGB888)
				{
					this->m_data->p_qimage->convertTo(QImage::Format_RGB888);
				}
				// 因为qimage在初始化时 同cv::mat使用同一块内存缓冲区，所以当类型相同时，cv的算法会直接作用在qimage上
				if (this->m_data->p_qimage->constBits() != this->m_data->m.data)
				{
					//int q_bytesline = this->m_data->p_qimage->bytesPerLine(); // 获取每一行长度
					//int cv_bytesline = this->m_data->m.step; // 获取每一行长度
					//uchar* q_data = (uchar*)this->m_data->p_qimage->constBits(); // 数据
					//uchar* cv_data = this->m_data->m.data;// 数据
					//int width = end_co.col - start_co.col;// 宽度

					////qDebug("q_image_bits = %d, q_image_constbits = %d, cv_image = %d", this->m_data->p_qimage->bits(), this->m_data->p_qimage->constBits(), this->m_data->m.data);

					//for (int i = start_co.row - 1; i < end_co.row; ++i)
					//{
					//	memcpy(&q_data[i * q_bytesline + start_co.col], &cv_data[i * cv_bytesline + start_co.col], width);
					//}

					uchar* cv_line = nullptr;
					for (int i = start_co.row; i < end_co.row; ++i)
					{
						for (int j = start_co.col; j < end_co.col; ++j)
						{
							cv_line = this->m_data->m.ptr<uchar>(i, j);
							this->m_data->p_qimage-> \
								setPixel(j, i,
									qRgb(cv_line[0], cv_line[1], cv_line[2]));
						}
					}

				}
				break;
			}
			case CV_8UC1:
			{
				// 因为qimage在初始化时 同cv::mat使用同一块内存缓冲区，所以当类型相同时，cv的算法会直接作用在qimage上
				// 所以当类型相同时，不需要做改变
				if (this->m_data->p_qimage->format() != QImage::Format_Grayscale8)
				{
					this->m_data->p_qimage->convertTo(QImage::Format_Grayscale8);
				}
				if (this->m_data->p_qimage->constBits() != this->m_data->m.data)
				{
					int q_bytesline = this->m_data->p_qimage->bytesPerLine(); // 获取每一行长度
					int cv_bytesline = this->m_data->m.step; // 获取每一行长度
					uchar* q_data = (uchar*)this->m_data->p_qimage->constBits(); // 数据
					uchar* cv_data = this->m_data->m.data;// 数据
					int width = end_co.col - start_co.col;// 宽度

					//qDebug("q_image_bits = %d, q_image_constbits = %d, cv_image = %d", this->m_data->p_qimage->bits(), this->m_data->p_qimage->constBits(), this->m_data->m.data);

					for (int i = start_co.row - 1; i < end_co.row; ++i)
					{
						memcpy(&q_data[i * q_bytesline + start_co.col], &cv_data[i * cv_bytesline + start_co.col], width);
					}
					//uchar* point = nullptr;
					//CMatrix& cimage = this->m_data->m;
					//for (int i = start_co.row; i < end_co.row; ++i)
					//{
					//	for (int j = start_co.col; j < end_co.col; ++j)
					//	{
					//		point = cimage.ptr<uchar>(i, j);
					//		this->m_data->p_qimage-> \
					//			setPixel(j, i, qRgb(*point, *point, *point));
					//	}
					//}
					
				}
				break;
			}
			default:
				qWarning("Image::syncPartQImage: image format is not matched, type is  %d", this->m_data->m.type());

				break;
			}
		}
	}

	void Image::syncTotalCMatrix()
	{
		QImage* p_qimage = this->m_data->p_qimage;
		if (p_qimage != nullptr)
		{
			switch (p_qimage->format())
			{
			case QImage::Format_RGB888:
				this->m_data->m = CMatrix(p_qimage->height(), p_qimage->width(), CV_8UC3, (void*)p_qimage->constBits(), p_qimage->bytesPerLine());
				break;
			case QImage::Format_Grayscale8:
				this->m_data->m = CMatrix(p_qimage->height(), p_qimage->width(), CV_8UC1, (void*)p_qimage->constBits(), p_qimage->bytesPerLine());
				break;
			default:
				qWarning("Image::syncTotalCMatrix: image format is not matched");
				break;
			}
		}
	}
	void Image::syncPartCMatrix(const Coordinates& start_co, const Coordinates& end_co)
	{
		QImage* p_qimage = this->m_data->p_qimage;
		if (p_qimage != nullptr)
		{
			switch (p_qimage->format())
			{
			case QImage::Format_RGB888:
				this->m_data->m = CMatrix(p_qimage->height(), p_qimage->width(), CV_8UC3, (void*)p_qimage->constBits(), p_qimage->bytesPerLine());
				break;
			case QImage::Format_Grayscale8:
				this->m_data->m = CMatrix(p_qimage->height(), p_qimage->width(), CV_8UC1, (void*)p_qimage->constBits(), p_qimage->bytesPerLine());
				break;
			default:
				qWarning("Image::syncTotalCMatrix: image format is not matched");
				break;
			}
		}
	}

	void Image::syncTotalQImageInThread()
	{
	}

	void Image::syncPartQImageInThread(const Coordinates& start_co, const Coordinates& end_co)
	{
	}

	void Image::syncTotalCMatrixInThread()
	{
	}

	void Image::syncPartCMatrixInThread(const Coordinates& start_co, const Coordinates& end_co)
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