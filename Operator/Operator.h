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
	private:
		Operator();
		Operator(const Operator&) = delete;
		Operator(Operator&&);
	public:
		~Operator();
	public:// �����洢
		String serialize();
		void deseriallize(String&& file_content);
		void deseriallize(String& file_content);
		void save(const Path& path);
	private:
		OperatorData* m_data;
	};

}
#endif // !__OPERATOR_H__
