#ifndef INCLUDED_RTG_TASKLIST_H
#define INCLUDED_RTG_TASKLIST_H

#include "ResourceHandler.h"
#include "Task.h"

namespace RTG
{
	template < typename Type >
	class TaskList
	{
		friend class DTask;
		Task*		m_pDummy;
	public:
		class Iterator
		{
			Task*		m_pTask;
			TaskList*	m_pTaskList;
		public:
			Iterator( TaskList* pList );
			Iterator( const Iterator& it );
			~Iterator();
			Iterator& operator ++();
			Iterator& operator --();
			Iterator& operator =( const Iterator& it );
			bool operator ==( const Iterator& it );
			bool operator !=( const Iterator& it );
			Type& operator*();
			void Begin();
			void Next();
			void End();
			void Remove();
		};
		TaskList();
		~TaskList();
		void Init();
		Type* Add( Type* pTask );
		void Delete( Type* pTask );
	};

	template < typename Type >
	TaskList < Type >::TaskList() : m_pDummy()
	{
	}

	template < typename Type >
	TaskList < Type >::~TaskList()
	{
		MAPIL::SafeDelete( m_pDummy );
	}

	template < typename Type >
	void TaskList < Type >::Init()
	{
		m_pDummy = new Task();
		m_pDummy->m_pPrev = m_pDummy;
		m_pDummy->m_pNext = m_pDummy;
	}

	template < typename Type >
	Type* TaskList < Type >::Add( Type* pTask )
	{
		pTask->m_pPrev = m_pDummy;
		pTask->m_pNext = m_pDummy->m_pNext;
		pTask->m_pNext->m_pPrev = pTask;
		m_pDummy->m_pNext = pTask;

		return pTask;
	}

	template < typename Type >
	void TaskList < Type >::Delete( Type* pTask )
	{
		pTask->m_pNext->m_pPrev = pTask->m_pPrev;
		pTask->m_pPrev->m_pNext = pTask->m_pNext;
		MAPIL::SafeDelete( pTask );
	}

	template < typename Type >
	TaskList < Type >::Iterator::Iterator( TaskList < Type >* pList ) : m_pTask( NULL ), m_pTaskList( pList )
	{
		m_pTask = m_pTaskList->m_pDummy;
	}

	template < typename Type >
	TaskList < Type >::Iterator::Iterator( const typename TaskList < Type >::Iterator& it ) : m_pTask( it.m_pTask ), m_pTaskList( it.m_pTaskList )
	{
	}

	template < typename Type >
	TaskList < Type >::Iterator::~Iterator()
	{
		m_pTask = NULL;
	}

	template < typename Type >
	typename TaskList < Type >::Iterator& TaskList < Type >::Iterator::operator ++()
	{
		m_pTask = (Type*)m_pTask->m_pNext;

		return *this;
	}

	template < typename Type >
	typename TaskList < Type >::Iterator& TaskList < Type >::Iterator::operator --()
	{
		m_pTask = m_pTask->m_pPrev;

		return *this;
	}

	template < typename Type >
	typename TaskList < Type >::Iterator& TaskList < Type >::Iterator::operator =( const typename TaskList < Type >::Iterator& it )
	{
		m_pTask = it.m_pTask;

		return *this;
	}

	template < typename Type >
	bool TaskList < Type >::Iterator::operator ==( const typename TaskList < Type >::Iterator& it )
	{
		return m_pTask == it.m_pTask;
	}

	template < typename Type >
	bool TaskList < Type >::Iterator::operator !=( const typename TaskList < Type >::Iterator& it )
	{
		return m_pTask != it.m_pTask;
	}

	template < typename Type >
	Type& TaskList < Type >::Iterator::operator *()
	{
		return *(Type*)m_pTask;
	}

	template < typename Type >
	void TaskList < Type >::Iterator::Begin()
	{
		m_pTask = (Type*)m_pTaskList->m_pDummy->m_pNext;
	}

	template < typename Type >
	void TaskList < Type >::Iterator::Next()
	{
		m_pTask = (Type*)m_pTask->m_pNext;
	}

	template < typename Type >
	void TaskList < Type >::Iterator::End()
	{
		m_pTask = m_pTaskList->m_pDummy;
	}

	template < typename Type >
	void TaskList < Type >::Iterator::Remove()
	{
		m_pTask = m_pTask->m_pPrev;
		m_pTaskList->Delete( (Type*)m_pTask->m_pNext );
	}

	template < typename Type >
	void DeleteTaskList( TaskList < Type >* pList )
	{
		TaskList < Type > ::Iterator it( pList );
		TaskList < Type > ::Iterator itEnd( pList );

		itEnd.End();
		
		for( it.Begin(); it != itEnd; ++it ){
			it.Remove();
		}
	}
}

#endif