#include"Operator.h"
#include<qqueue.h>
#include"../Image/Image.h"
namespace PhotoEdit {
	class Operator::OperatorData
	{
		// �������������
		Image* image;
		Image::Coordinates start_co;
		Image::Coordinates end_co;

		int operator_type;// ��������
		int storage_location;// �洢λ�� �����ڴ滹�Ǵ�����
	};
}
