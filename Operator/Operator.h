#ifndef __OPERATOR_H__
#define __OPERATOR_H__
#include<string>
#include<boost/filesystem.hpp>
// ���� ���Խ������в���������������ջ
namespace PhotoEdit {
	class Operator
	{
	public:
		friend class OperatorFactory;
	public:
		using String = std::string;
		using Path = boost::filesystem::path;
	private:
		class OperatorData;
	public:
		Operator();
		Operator(const Operator&);
		Operator(Operator&&);
	public:
		~Operator();
	public:// �����洢
		int writeFile();
		int readFile();
	private:
		OperatorData* m_data;
	};

}
#endif // !__OPERATOR_H__
