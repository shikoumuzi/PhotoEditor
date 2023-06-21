#include"Operator.h"
#include<qqueue.h>
#include"../Image/Image.h"
namespace PhotoEdit {
	class Operator::OperatorData
	{
		int storage_status;// 在内存中还是文件中
		
		Image* image;// 操作对象
		Image::Coordinates start_co;// 坐标
		Image::Coordinates end_co;
		Path file_path;
		int operator_type;// 操作类型
	};
	Operator::Operator(Operator&&)
	{
	}
	Operator::~Operator()
	{
	}
	int Operator::writeFile()
	{
		return 0;
	}
	int Operator::readFile()
	{
		return 0;
	}
}
