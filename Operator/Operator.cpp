#include"Operator.h"
#include<qqueue.h>
#include"../Image/Image.h"
namespace PhotoEdit {
	class Operator::OperatorData
	{
		int storage_status;// ���ڴ��л����ļ���
		
		Image* image;// ��������
		Image::Coordinates start_co;// ����
		Image::Coordinates end_co;
		Path file_path;
		int operator_type;// ��������
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
