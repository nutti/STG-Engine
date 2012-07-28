#include "Effect.h"

namespace RTG
{
	Effect::Effect() : Task()
	{
	}

	Effect::~Effect()
	{
	}

	bool Effect::Update()
	{
		bool ret = Move();

		Draw();
		
		return ret;
	}

	void Effect::Draw()
	{
	}

	bool Effect::Move()
	{
		return true;
	}
}