#ifndef INCLUDED_RTG_CIRCLEENEMY_H
#define INCLUDED_RTG_CIRCLEENEMY_H

#include "CircleObj.h"
#include "TaskList.hpp"
#include "CircleEnemyShot.h"
#include "Defines.h"

namespace RTG
{
	class CircleEnemy : public CircleObj
	{
	protected:
		TaskList < CircleEnemyShot >*		m_pShotList;
		double								m_Angle;
		int									m_Counter;
		double								m_Speed;
		int									m_HP;
		int									m_Score;
		bool								m_IsBoss;
	public:
		CircleEnemy(	TaskList < CircleEnemyShot >* pList,
						const MAPIL::Vector2 < double >& vPos,
						double speed,
						double angle,
						double radius,
						int hp,
						int score );
		virtual ~CircleEnemy();
		virtual void Draw() = 0;
		virtual bool Move() = 0;
		virtual void Damage( int dec );
		virtual int GetHP() const;
		int GetScore() const;
		bool IsBoss() const;
	};
}

#endif