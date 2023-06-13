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
			Coordinates(Image* parent, int row, int col):parent(parent), row(row), col(col){}
			~Coordinates()
			{
				this->parent = nullptr;
			}
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
		bool imread(Path& path);
		bool imshow(String& windows_title);
	public: // ת������
		QImage* toQImage();
		QPixmap* toQPixmap();
		cv::Mat* toMat();
	public: // ���ٺ���
		void finalize(void * image);
	public:// �ı亯��
		CMatrix* dilate(CMatrix& cm, int iterator_times = 10, int OPTION = IMAGE_FLAG::DEFAULT, int range_rows = -1, int range_cols = -1);
		CMatrix* erode(CMatrix& cm, int iterator_times = 10, int OPTION = IMAGE_FLAG::DEFAULT, int range_rows = -1, int range_cols = -1);
		CMatrix* watershed(int value, int OPTION = IMAGE_FLAG::DEFAULT, int range_rows = -1, int range_cols = -1);
		CMatrix* thresold(int value, int OPTION = IMAGE_FLAG::DEFAULT, int range_rows = -1, int range_cols = -1);
		CMatrix* distanceTransform(int value, int OPTION = IMAGE_FLAG::DEFAULT, int range_rows = -1, int range_cols = -1);
		
	public:// ����ͬ������
		void synchronization();

		static void cv2eigenC3(CMatrix&, EMatrix&);
		static void eigen2cvC3(EMatrix&, CMatrix&);
		static void eigen2qimage(EMatrix&, QImage&);
	private:
		struct ImageData *m_data;
	};




}


#endif // !__IMAGE_H__
