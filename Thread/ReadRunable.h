#ifndef __READRUNABLE_H__
#define __READRUNABLE_H__

#include<qthread.h>
#include"../WorkSpace/workspace.h"
#include<qrunnable.h>
namespace PhotoEdit
{
	class ReadRunable : public QRunnable
	{
	public:
		using ReadFun = void(*)(WorkSpace*);
	public:
		ReadRunable(ReadFun fun, WorkSpace* parent) :fun(fun), parent(parent) {}

		void run() override
		{
			this->fun(parent);
		}
	private:
		ReadFun fun;
		WorkSpace* parent;

	};
}


#endif // !__READTHREAD_H__
