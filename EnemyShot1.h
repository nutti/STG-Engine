#ifndef INCLUDED_RTG_ENEMYSHOT1_H
#define INCLUDED_RTG_ENEMYSHOT1_H

#include "CircleEnemyShot.h"

namespace RTG
{
	class EnemyShot1 : public CircleEnemyShot
	{
	private:
	public:
		EnemyShot1(	const MAPIL::Vector2 < double >& vPos,
					double speed,
					double angle,
					double radius );
		EnemyShot1(	const MAPIL::Vector2 < double >& vPos,
					double speed,
					double angle,
					double radius,
					int imgID );
		virtual ~EnemyShot1();
		virtual void Draw();
		virtual bool Move();
	};
}

#endif