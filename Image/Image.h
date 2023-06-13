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

	public:// 读取函数
		bool imread(Path& path);
		bool imshow(String& windows_title);
	public: // 转换函数
		QImage* toQImage();
		QPixmap* toQPixmap();
		cv::Mat* toMat();
	public: // 销毁函数
		void finalize(void * image);
	public:// 改变函数
		CMatrix* dilate(CMatrix& cm, int iterator_times = 10, int OPTION = IMAGE_FLAG::DEFAULT);
		CMatrix* dilate(CMatrix& cm, int iterator_times = 10, Coordinates& start_co, Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);

		CMatrix* erode(CMatrix& cm, int iterator_times = 10, int OPTION = IMAGE_FLAG::DEFAULT);
		CMatrix* erode(CMatrix& cm, int iterator_times = 10, Coordinates& start_co, Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);

		CMatrix* watershed(int value, int OPTION = IMAGE_FLAG::DEFAULT);
		CMatrix* watershed(int value, Coordinates& start_co, Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);

		CMatrix* thresold(int value, int OPTION = IMAGE_FLAG::DEFAULT);
		CMatrix* thresold(int value, Coordinates& start_co, Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);

		CMatrix* distanceTransform(int value, int OPTION = IMAGE_FLAG::DEFAULT);
		CMatrix* distanceTransform(int value, Coordinates& start_co, Coordinates& end_co, int OPTION = IMAGE_FLAG::DEFAULT);
		
	public:// 数据同步函数
		void syncTotalQImage();
		void syncPartQImage(Coordinates& start_co, Coordinates& end_co);
		void syncTotalCMatrix();
		void syncPartCMatrix(Coordinates& start_co, Coordinates& end_co);

		void syncTotalQImageInThread();
		void syncPartQImageInThread(Coordinates& start_co, Coordinates& end_co);
		void syncTotalCMatrixInThread();
		void syncPartCMatrixInThread(Coordinates& start_co, Coordinates& end_co);
	public:// 转换接口
		static void cv2eigenC3(CMatrix&, EMatrix&);
		static void eigen2cvC3(EMatrix&, CMatrix&);
		static void eigen2qimageC3(EMatrix&, QImage&);
	private:
		struct ImageData *m_data;
	};




}


#endif // !__IMAGE_H__
