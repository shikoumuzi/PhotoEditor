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
		class Coordinates
		{
		public:
			static Coordinates null;
		public:
			Coordinates();
			Coordinates(Image* parent, int row, int col);
			~Coordinates();
		public:
			void operator=(Coordinates&);
		public:
			int row;
			int col;
			Image* parent;
		};
	public:
		using Path = boost::filesystem::path;
		using EVector = Eigen::Vector3d;
		using EMatrix = Eigen::Matrix<EVector, Eigen::Dynamic, Eigen::Dynamic>;
		using CMatrix = cv::Mat;
		using String = std::string;
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
		~Image();

	public:// ��ȡ����
		int imread(Path& path);
		int imshow(const String& windows_title);
		static int imshow(const CMatrix& cmatrix, const String& windows_title);

	public: // ת������
		QImage* toQImage();
		QPixmap* toQPixmap();
		cv::Mat* toMat();

	public: // ���ٺ���
		void finalize(void * image);

	public: // ���ݱ���
		int save(Path& path);

	public:// �ı亯��
		CMatrix* dilate(int& error_no, CMatrix& kernel, int iterator_times = 3, int OPTION = IMAGE_FLAG::DEFAULT);
		CMatrix* dilate(int& error_no, CMatrix& kernel, Coordinates& start_co, Coordinates& end_co, int iterator_times = 10,  int OPTION = IMAGE_FLAG::DEFAULT);

		CMatrix* erode(int& error_no, CMatrix& kernel, int iterator_times = 3, int OPTION = IMAGE_FLAG::DEFAULT);
		CMatrix* erode(int& error_no, CMatrix& kernel, Coordinates& start_co, Coordinates& end_co, int iterator_times = 10, int OPTION = IMAGE_FLAG::DEFAULT);

		CMatrix* watershed(int& error_no, int value, int OPTION = IMAGE_FLAG::DEFAULT);
		CMatrix* watershed(int& error_no, int value, Coordinates& start_co, Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);

		CMatrix* thresold(int& error_no, int value, int OPTION = IMAGE_FLAG::DEFAULT);
		CMatrix* thresold(int& error_no, int value, Coordinates& start_co, Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);

		CMatrix* distanceTransform(int value, int OPTION = IMAGE_FLAG::DEFAULT);
		CMatrix* distanceTransform(int value, Coordinates& start_co, Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);
		
	public:// ����ͬ������
		void syncTotalQImage();
		void syncPartQImage(Coordinates& start_co, Coordinates& end_co);
		void syncTotalCMatrix();
		void syncPartCMatrix(Coordinates& start_co, Coordinates& end_co);

		void syncTotalQImageInThread();
		void syncPartQImageInThread(Coordinates& start_co, Coordinates& end_co);
		void syncTotalCMatrixInThread();
		void syncPartCMatrixInThread(Coordinates& start_co, Coordinates& end_co);

	public:// ת���ӿ�
		static void cv2eigenC3(CMatrix&, EMatrix&);
		static void eigen2cvC3(EMatrix&, CMatrix&);
		static void eigen2qimageC3(EMatrix&, QImage&);
	private:
		struct ImageData *m_data;
	};




}


#endif // !__IMAGE_H__
