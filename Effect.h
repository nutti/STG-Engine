#ifndef INCLUDED_RTG_EFFECT_H
#define INCLUDED_RTG_EFFECT_H

#include "Task.h"

namespace RTG
{
	class Effect : public Task
	{
	public:
		Effect();
		virtual ~Effect();
		bool Update();
		virtual void Draw();
		virtual bool Move();
	};
}

#endif