#include "CircleEnemyShot.h"

namespace RTG
{
	CircleEnemyShot::CircleEnemyShot(	const MAPIL::Vector2 < double >& vPos,
										double speed,
										double angle,
										double radius ) :	CircleObj( vPos, radius ),
															m_Speed( speed ),
															m_Angle( angle )
	{
	}

	CircleEnemyShot::~CircleEnemyShot()
	{
	}

	void CircleEnemyShot::Reflect()
	{
		m_Angle += 180;
	}

	int CircleEnemyShot::GetImgID()
	{
		return m_ImgID;
	}
}