#include"Operator.h"
#include<qqueue.h>
#include"../Image/Image.h"
#include"../Coordinates/Coordinates.h"
namespace PhotoEdit {
	class Operator::OperatorData
	{
		int storage_status;// ���ڴ��л����ļ���
		
		Image* image;// ��������
		Coordinates start_co;// ����
		Coordinates end_co;
		Path file_path;
		int operator_type;// ��������
	};
	Operator::Operator()
	{

	}

	Operator::Operator(const Operator&)
	{

	}
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
