#include <iostream>

#include "ResourceHandler.h"

#include "Task.h"

namespace RTG
{
	Task::Task() : m_pNext( NULL ), m_pPrev( NULL )
	{
	}

	Task::~Task()
	{
		m_pNext = NULL;
		m_pPrev = NULL;
	}

	void* Task::operator new( size_t size )
	{
		ResourceHandler* pRH = ResourceHandler::GetInst();
		void* p = pRH->AllocMemory();
		//std::cout << "( Alloc ) Rest blocks : " << pRH->m_Alloc.GetNumRestBlocks() << " Address : " << p;
		//std::cout << " Size : " << size << std::endl;
		return p;
	}

	void Task::operator delete( void* p )
	{
		ResourceHandler* pRH = ResourceHandler::GetInst();
		pRH->ReleaseMemory( p );
		//std::cout << "( Free ) Rest blocks : " << pRH->m_Alloc.GetNumRestBlocks() << " Address : " << p << std::endl;
	}
}