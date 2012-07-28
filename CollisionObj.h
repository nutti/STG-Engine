#ifndef INCLUDED_RTG_COLLISIONOBJ_H
#define INCLUDED_RTG_COLLISIONOBJ_H

#include "Task.h"

namespace RTG
{
	class CollisionObj : public Task
	{
	public:
		CollisionObj();
		virtual ~CollisionObj();
		bool Update();
		virtual void Draw();
		virtual bool Move();
	};
}

#endif