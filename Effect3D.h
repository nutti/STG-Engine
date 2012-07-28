#ifndef INCLUDED_RTG_EFFECT3D_H
#define INCLUDED_RTG_EFFECT3D_H

#include "Effect.h"

namespace RTG
{
	class Effect3D : public Effect
	{
	public:
		Effect3D();
		virtual ~Effect3D();
		virtual void Draw();
		virtual bool Move();
	};
}

#endif