#ifndef INCLUDED_RTG_REFLECTEDSHOT1_H
#define INCLUDED_RTG_REFLECTEDSHOT1_H

#include "CircleReflectedShot.h"
#include "CircleEnemyShot.h"
#include "NormalPlayer.h"

namespace RTG
{
	class ReflectedShot1 : public CircleReflectedShot
	{
		int			m_TextureIndex;
	public:
		ReflectedShot1(	const CircleEnemyShot& shot,
						const NormalPlayer& player,
						int textureIndex );
		~ReflectedShot1();
		void Draw();
		bool Move();
	};
}

#endif