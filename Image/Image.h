#ifndef __IMAGE_H__
#define __IMAGE_H__
#include<qpixmap.h>
#include<qimage>
#include<qstring.h>
#include<Eigen/Core>
#include<opencv2/core/core.hpp> 
#include<opencv2/highgui/highgui.hpp>   
#include<boost/filesystem/path.hpp>
#include<string>
#include<future>
#include"../Error/error.h"

namespace PhotoEdit {
	class Image
	{
	public:
		using Path = boost::filesystem::path;
		using EVector = Eigen::Vector3d;
		using EMatrix = Eigen::Matrix<EVector, Eigen::Dynamic, Eigen::Dynamic>;
		using CMatrix = cv::Mat;
		using String = std::string;
		using PImage = Image*;
	public:
		class Coordinates
		{
		public:
			static Coordinates null;
		public:
			Coordinates();
			Coordinates(Image* parent, int row, int col);
			Coordinates(Image& parent, int row, int col);
			~Coordinates();
		public:
			void operator=(Coordinates&);
		public:
			int row;
			int col;
			Image* parent;
		};
		struct CMatrixPair
		{
			Image::CMatrix* src;
			Image::CMatrix* dst;
		};

	public:
		enum IMAGE_FLAG
		{
			DEFAULT = 0,
			NEWOBJECT,
			
		};
	public: 
		struct ImageData;
	public:
		Image();
		Image(CMatrix& cm);
		~Image();

	public:// ��ȡ����
		int imRead(Path& path);
		int imShow(const String& windows_title);
		int imShowNoWait(const String& windows_title);
		static int imShow(const QImage& image, const String& windows_title);
		static int imShowNoWait(const QImage& image, const String& windows_title);
		static int imShow(const CMatrix& cmatrix, const String& windows_title);
		static int imShowNoWait(const CMatrix& cmatrix, const String& windows_title);
		inline static void waitkey();

	public: // ת������
		QImage* toQImage();
		QPixmap* toQPixmap();
		cv::Mat* toMat();

	public:// ������Ϣ
		inline bool isempty();
		int rows();
		int cols();

	public: // ���ٺ���
		void finalize(void * image);

	public: // ���ݱ���
		int save(Path& path);

	public:
		int copyTo(Image& image);

	public:// �ı亯��
		Image* Rgb2Gray(int& error_no, int OPTION = IMAGE_FLAG::DEFAULT);

		Image* dilate(int& error_no, CMatrix& kernel, int iterator_times = 3, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* dilate(int& error_no, CMatrix& kernel, const Coordinates& start_co, const Coordinates& end_co, int iterator_times = 10,  int OPTION = IMAGE_FLAG::DEFAULT);

		Image* erode(int& error_no, CMatrix& kernel, int iterator_times = 3, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* erode(int& error_no, CMatrix& kernel, const Coordinates& start_co, const Coordinates& end_co, int iterator_times = 10, int OPTION = IMAGE_FLAG::DEFAULT);

		Image* watershed(int& error_no, int value, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* watershed(int& error_no, int value, const Coordinates& start_co, const Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);

		Image* thresold(int& error_no, int value, int max = 255, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* thresold(int& error_no, int value, const Coordinates& start_co, const Coordinates& end_co, int max = 255, int OPTION = IMAGE_FLAG::DEFAULT);

		Image* distanceTransform(int& error_no, int value, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* distanceTransform(int& error_no, int value, const Coordinates& start_co, const Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);

	public: // ��������

		inline Image* operator+(Image&);
		inline Image* operator+=(Image&);
		Image* operator+(int);
		Image* operator+=(int);
		Image* operator-(Image&);
		Image* operator-=(Image&);
		Image* operator-(int);
		Image* operator-=(int);
		Image* operator*(Image&);
		Image* operator*=(Image&);
		Image* operator*(int);
		Image* operator*=(int);
		Image* operator/(Image&);
		Image* operator/=(Image&);

		Image* add(Image&, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* sub(Image&, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* mut(Image&, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* divide(Image&, int OPTION = IMAGE_FLAG::DEFAULT);

		Image* T();
		Image& rotateLeft();
		Image& rotateRight();

	public:
		Image* offsetAll(int offsetvalue, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetAll(int offsetvalue, const Coordinates& start_co, const Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetR(int offsetvalue, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetR(int offsetvalue, const Coordinates& start_co, const Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetG(int offsetvalue, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetG(int offsetvalue, const Coordinates& start_co, const Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetB(int offsetvalue, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetB(int offsetvalue, const Coordinates& start_co, const Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetB(int RGB_BIT, int offsetvalue, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetTwoOfRGB(int RGB_BIT, int offsetvalue, const Coordinates& start_co, const Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);
	private:
		CMatrix* createObject(int& error_no, int OPTION);
		CMatrixPair createPartObject(int& error_no, const Coordinates& start_co, const Coordinates& end_co, int OPTION);
		Image* returnResult(CMatrix* cm);
		Image* Image::returnResult(CMatrixPair& cm);

	public:// ����ͬ������
		void syncTotalQImage();
		void syncPartQImage(const Coordinates& start_co, const Coordinates& end_co);
		void syncTotalCMatrix();
		void syncPartCMatrix(const Coordinates& start_co, const Coordinates& end_co);

		void syncTotalQImageInThread();
		void syncPartQImageInThread(const Coordinates& start_co, const Coordinates& end_co);
		void syncTotalCMatrixInThread();
		void syncPartCMatrixInThread(const Coordinates& start_co, const Coordinates& end_co);

	public:// ת���ӿ�
		static void cv2eigenC3(CMatrix&, EMatrix&);
		static void eigen2cvC3(EMatrix&, CMatrix&);
		static void eigen2qimageC3(EMatrix&, QImage&);
	private:
		struct ImageData *m_data;
	};




}


#endif // !__IMAGE_H__
