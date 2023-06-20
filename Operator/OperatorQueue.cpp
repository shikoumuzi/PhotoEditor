#include "OperatorQueue.h"
#include<deque>
#include<boost/filesystem.hpp>
namespace PhotoEdit {

	struct OperatorQueue::MemoryView::MemoryViewData
	{
		int current_pos;
		int start;
		int end;
		std::deque<Operator>* queue;

	};

	class OperatorQueue::OperatorQueueData
	{
	public:
		MemoryView view;
		std::deque<Operator> queue;
		static size_t length;
		int current_pos;
	};

	size_t OperatorQueue::OperatorQueueData::length = 14;

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
			if (offset < 0)
			{
				if ((this->m_data->start - 1) >= 0)
				{
					--this->m_data->start;
				}
				else
				{

				}

			}
			else
			{
				if ((this->m_data->end + 1) < OperatorQueue::OperatorQueueData::length)
				{
					++this->m_data->end;
				}
			}
		}

	
	}

	OperatorQueue::OperatorQueue():m_data(new OperatorQueueData)
	{

	}

	void OperatorQueue::push(Operator&& operation)
	{
		this->m_data->queue.emplace_back(operation);
		this->m_data->current_pos = this->m_data->queue.size();
		if (this->m_data->queue.size() > this->m_data->length)
		{
			this->pop();
			this->m_data->current_pos -= 1;
		}
	}

	void OperatorQueue::pop()
	{
		this->m_data->queue.pop_back();
		this->m_data->current_pos -= 1; 
	}

	void OperatorQueue::clear(int pos, int num)
	{
		for (int i = pos + 1; i < this->m_data->length; ++i)
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
