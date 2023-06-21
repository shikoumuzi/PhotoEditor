#ifndef __OPERATOR_H__
#define __OPERATOR_H__
#include<string>
#include<boost/filesystem.hpp>
// 父类 用以结算所有操作，并包含操作栈
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
	private:
		Operator();
		Operator(const Operator&) = delete;
	public:
		Operator(Operator&&);
	public:
		~Operator();
	public:// 操作存储
		int writeFile();
		int readFile();
	private:
		OperatorData* m_data;
	};

}
#endif // !__OPERATOR_H__
