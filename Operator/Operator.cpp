#include"Operator.h"
#include<qqueue.h>
#include"../Image/Image.h"
namespace PhotoEdit {
	class Operator::OperatorData
	{
		// 操作对象和坐标
		Image* image;
		Image::Coordinates start_co;
		Image::Coordinates end_co;

		int operator_type;// 操作类型
		int storage_location;// 存储位置 是在内存还是磁盘上
	};
}
