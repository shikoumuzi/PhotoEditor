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
#include"../Coordinates/Coordinates.h"
#include<vector>
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
		using ByteVector = std::vector<char>;
	public:
		struct CMatrixPair
		{
			Image::CMatrix* src;
			Image::CMatrix* total_dst;
			Image::CMatrix* part_dst;
		};
	public:
		enum IMAGE_FLAG
		{
			DEFAULT = 0,
			NEWOBJECT,
			
		};
		enum IMAGE_COLOR
		{
			BLUE = 1,
			GREEN = 2,
			RED = 4
		};
	public: 
		struct ImageData;
	public:
		Image();
		Image(CMatrix& cm);
		~Image();

	public:// ��ȡ����
		int imRead(const Path& path);
		int imRead(const String& path, int);
		int imRead(const ByteVector& bytes);
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

		Image* add(int& error_no, Image&, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* sub(int& error_no, Image&, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* mut(int& error_no, Image&, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* divide(int& error_no, Image&, int OPTION = IMAGE_FLAG::DEFAULT);

		Image* T();
		Image& rotateLeft();
		Image& rotateRight();

	public:
		Image* offsetAll(int& error_no, int offsetvalue, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetAll(int& error_no, int offsetvalue, const Coordinates& start_co, const Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetR(int& error_no, int offsetvalue, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetR(int& error_no, int offsetvalue, const Coordinates& start_co, const Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetG(int& error_no, int offsetvalue, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetG(int& error_no, int offsetvalue, const Coordinates& start_co, const Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetB(int& error_no, int offsetvalue, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetB(int& error_no, int offsetvalue, const Coordinates& start_co, const Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offset(int& error_no, int offsetvalue, int COLOR, const Coordinates& start_co, const Coordinates& end_co, bool is_part = false, int OPTION = IMAGE_FLAG::DEFAULT);

		Image* offsetRGB(int& error_no, int RGB_BIT, int offsetvalue_r, int offsetvalue_g, int offsetvalue_b, int OPTION = IMAGE_FLAG::DEFAULT);
		Image* offsetRGB(int& error_no, int RGB_BIT, int offsetvalue_r, int offsetvalue_g, int offsetvalue_b, const Coordinates& start_co, const Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);

	private:
		CMatrix* createObject(int& error_no, int OPTION);
		CMatrixPair createPartObject(int& error_no, const Coordinates& start_co, const Coordinates& end_co, int OPTION);
		int checkCoordinates(const Coordinates& start_co, const Coordinates& end_co);
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
