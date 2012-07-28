#include "CircleEnemy.h"

namespace RTG
{
	CircleEnemy::CircleEnemy(	TaskList < CircleEnemyShot >* pList,
								const MAPIL::Vector2 < double >& vPos,
								double speed,
								double angle,
								double radius,
								int hp,
								int score ) :	CircleObj( vPos, radius ),
												m_Speed( speed ),
												m_Angle( angle ),
												m_pShotList( pList ),
												m_Counter( 0 ),
												m_HP( hp ),
												m_Score( score ),
												m_IsBoss( false )
	{
	}

	CircleEnemy::~CircleEnemy()
	{
		m_pShotList = NULL;
	}

	void CircleEnemy::Damage( int dec )
	{
		m_HP -= dec;
	}

	int CircleEnemy::GetHP() const
	{
		return m_HP;
	}

	int CircleEnemy::GetScore() const
	{
		return m_Score;
	}

	bool CircleEnemy::IsBoss() const
	{
		return m_IsBoss;
	}
}