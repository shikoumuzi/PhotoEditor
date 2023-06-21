#include "OperatorQueue.h"
#include<deque>
#include<boost/filesystem.hpp>
namespace PhotoEdit {

	struct OperatorQueue::MemoryView::MemoryViewData
	{
		size_t current_pos;
		int start;
		int end;
		std::deque<Operator>* queue;

	};

	class OperatorQueue::OperatorQueueData
	{
	public:
		OperatorQueueData() 
		{
			this->view.m_data->queue = &this->queue;
			this->current_pos = 0;
			this->current_pos = &this->view.m_data->current_pos;
		}
	public:
		inline int& start()
		{
			return this->view.m_data->start;
		}
		inline int& end()
		{
			return this->view.m_data->end;
		}
	public:
		std::deque<Operator> queue;
		MemoryView view;
		static size_t length;
		size_t* current_pos;
	};

	size_t OperatorQueue::OperatorQueueData::length = 14;

	OperatorQueue::MemoryView::MemoryView()
	{
	}

	OperatorQueue::MemoryView::MemoryView(void* data):m_data(new MemoryViewData)
	{
		this->m_data->start = 0;
		this->m_data->end = 0;
		this->m_data->current_pos = 0;
		this->m_data->queue = static_cast<std::deque<Operator>*>(data);
	}

	OperatorQueue::MemoryView::~MemoryView()
	{
		this->m_data->start = 0;
		this->m_data->end = 0;
		this->m_data->current_pos = 0;
		this->m_data->queue = nullptr;

		delete this->m_data;
		this->m_data = nullptr;

	}

	Operator& OperatorQueue::MemoryView::currentOperator()
	{
		return this->m_data->queue->operator[]( this->m_data->current_pos);
		
	}

	void OperatorQueue::MemoryView::move(int offset)
	{
		int& start = this->m_data->start;
		int& end = this->m_data->end;
		if (end - start < 6)
		{
			// 如果end和start之间差距不超过6 则表示不超过内存视窗

			if (offset < 0)
			{
				if ((this->m_data->start - 1) >= 0)
				{
					--this->m_data->start;
					// 拓展后读取对应内容
					this->m_data->queue->operator[](this->m_data->start).readFile();
					if(this->m_data->end - this->m_data->current_pos > 2)// 代表撤回了操作，不用写入文件
						this->m_data->queue->operator[](this->m_data->end).writeFile();
				}
				if ((this->m_data->current_pos - 1) >= 0)
				{
					--this->m_data->current_pos;
				}
			}
			else
			{
				if ((this->m_data->end + 1) < OperatorQueue::OperatorQueueData::length)
				{
					++this->m_data->end;
					// 拓展后读取对应内容
					this->m_data->queue->operator[](this->m_data->end).readFile();
				}
				if ((this->m_data->current_pos + 1) < OperatorQueue::OperatorQueueData::length)
				{
					++this->m_data->current_pos;
				}
			}
		}
		else
		{
			if (offset < 0)
			{
				if ((this->m_data->start - 1) >= 0)
				{
					--this->m_data->start;
					--this->m_data->current_pos;
					// 拓展后读取对应内容
					this->m_data->queue->operator[](this->m_data->start).readFile();
				}
			}
			else
			{
				if ((this->m_data->end + 1) < OperatorQueue::OperatorQueueData::length)
				{
					++this->m_data->end;
					// 拓展后读取对应内容
					this->m_data->queue->operator[](this->m_data->end).readFile();
					++this->m_data->current_pos;
				}
			}
		}

	
	}

	OperatorQueue::OperatorQueue():m_data(new OperatorQueueData){}

	OperatorQueue::~OperatorQueue()
	{
		delete this->m_data;
		this->m_data = nullptr;
	}

	void OperatorQueue::push(Operator&& operation)
	{
		// 先清除当前所有的累积栈
		this->clear(*this->m_data->current_pos);
		if (this->m_data->view.m_data->end > *this->m_data->current_pos)
		{
			this->pop();
			this->m_data->current_pos -= 1;
		}
		this->m_data->view.m_data->end = *this->m_data->current_pos;
		this->m_data->queue.emplace_back(operation);
		*this->m_data->current_pos = this->m_data->queue.size();

	}

	void OperatorQueue::pop()
	{
		this->m_data->queue.pop_back();
		if(this->m_data->current_pos - 1 >= 0)
			this->m_data->current_pos -= 1;
		if (this->m_data->start() - 1 >= 0)
			this->m_data->start() -= 1;
		if (this->m_data->end() - 1 >= 0)
			this->m_data->end() -= 1;
	}

	void OperatorQueue::clear(int pos)
	{
		for (int i = pos + 1; i < this->m_data->length || i < this->m_data->queue.size(); ++i)
		{
			this->m_data->queue.pop_back();
		}
	}

	void OperatorQueue::move(int offset)
	{
		this->m_data->view.move(offset);
	}

	void OperatorQueue::readStorage()
	{

	}

	void OperatorQueue::writerStorage()
	{

	}

	void PhotoEdit::OperatorQueue::earseTempFile()
	{

	}

	void PhotoEdit::OperatorQueue::createTempFile()
	{

	}


}
