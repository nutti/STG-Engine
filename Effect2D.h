#ifndef INCLUDED_RTG_EFFECT2D_H
#define INCLUDED_RTG_EFFECT2D_H

#include "Effect.h"

namespace RTG
{
	class Effect2D : public Effect
	{
	public:
		Effect2D();
		virtual ~Effect2D();
		bool Update();
		virtual void Draw();
		virtual bool Move();
	};
}

#endif