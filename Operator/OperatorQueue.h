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
		public:// 获取当前操作视图
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

	public:// 进出队列
		void push(Operator&& operation);// 压入操作
		void pop();// 弹出队头
		void clear(int pos, int num);//清理pos后所有栈
		void move(int offset);// 移动内存视窗

	private:// 图像在内存和磁盘交互的操作
		void readStorage();
		void writerStorage();
		void earseTempFile();
		void createTempFile();

	private:
		OperatorQueueData* m_data;

	};
}


#endif // !__OPERATORQUEUE_H__