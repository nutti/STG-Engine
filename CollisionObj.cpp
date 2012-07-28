#include "CollisionObj.h"

namespace RTG
{
	CollisionObj::CollisionObj() : Task()
	{
	}

	CollisionObj::~CollisionObj()
	{
	}

	bool CollisionObj::Update()
	{
		bool ret = Move();

		Draw();
		
		return ret;
	}

	void CollisionObj::Draw()
	{
	}

	bool CollisionObj::Move()
	{
		return true;
	}
}