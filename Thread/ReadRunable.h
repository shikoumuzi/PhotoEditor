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
		ReadRunable(WorkSpace* parent):parent(parent) {}

		void run() override
		{
			if(parent->isPathExit())
				this->parent->loadImage();
		}
	private:
		WorkSpace* parent;

	};
}


#endif // !__READTHREAD_H__
