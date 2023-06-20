#ifndef __OPERATORQUEUE_H__
#define __OPERATORQUEUE_H__
#include"../Operator/Operator.h"

namespace PhotoEdit {

	class OperatorQueue
	{
	private:
		friend class MemoryView;
		class OperatorQueueData;

	private:
		class MemoryView
		{
		public:
			struct MemoryViewData;
		public:// ��ȡ��ǰ������ͼ
			Operator& currentOperator();

		public:
			void move(int offset);

		public:
			MemoryViewData* m_data;
		};

	public:
		static OperatorQueue queue;
		OperatorQueue& getOperatorQueue()
		{
			return OperatorQueue::queue;
		}

	private:
		OperatorQueue();
	public:
		~OperatorQueue();

	public:// ��������
		void push(Operator&& operation);// ѹ�����
		void pop();// ������ͷ
		void clear(int pos, int num);//����pos������ջ
		void move(int offset);// �ƶ��ڴ��Ӵ�

	private:// ͼ�����ڴ�ʹ��̽����Ĳ���
		void readStorage();
		void writerStorage();
		void earseTempFile();
		void createTempFile();

	private:
		OperatorQueueData* m_data;

	};
}


#endif // !__OPERATORQUEUE_H__