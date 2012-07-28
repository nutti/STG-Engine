#include "Effect2D.h"

namespace RTG
{
	Effect2D::Effect2D() : Effect()
	{
	}

	Effect2D::~Effect2D()
	{
	}

	bool Effect2D::Update()
	{
		bool ret = Move();

		Draw();
		
		return ret;
	}

	void Effect2D::Draw()
	{
	}

	bool Effect2D::Move()
	{
		return true;
	}
}