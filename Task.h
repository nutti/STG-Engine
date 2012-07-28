#ifndef INCLUDED_RTG_TASK_H
#define INCLUDED_RTG_TASK_H

#include "Defines.h"

namespace RTG
{
	class Task
	{
	public:
		Task*		m_pNext;
		Task*		m_pPrev;
		
		Task();
		virtual ~Task();
		void* operator new( size_t size );
		void operator delete( void* p );
	};
}

#endif