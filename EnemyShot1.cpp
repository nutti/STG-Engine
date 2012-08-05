#include "EnemyShot1.h"

#include "ResourceHandler.h"

namespace RTG
{
	EnemyShot1::EnemyShot1(	const MAPIL::Vector2 < double >& vPos,
							double speed,
							double angle,
							double radius ) :	CircleEnemyShot( vPos, speed, angle, 3.0f )
	{
	}

	EnemyShot1::EnemyShot1(	const MAPIL::Vector2 < double >& vPos,
							double speed,
							double angle,
							double radius,
							int imgID ) :	CircleEnemyShot( vPos, speed, angle, radius )
	{
		m_ImgID = imgID;
	}

	EnemyShot1::~EnemyShot1()
	{
		m_ImgID = 0;
	}

	void EnemyShot1::Draw()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		MAPIL::DrawTexture(	p->GetTextureHandle( m_ImgID ), m_Pos.m_X, m_Pos.m_Y, 0.0f );
	}

	bool EnemyShot1::Move()
	{
		m_Pos.m_X += m_Speed * cos( m_Angle );
		m_Pos.m_Y -= m_Speed * sin( m_Angle );

		++m_Counter;

		if( m_Pos.m_X > 640.0f || m_Pos.m_X < 0.0f || m_Pos.m_Y > 480.0f || m_Pos.m_Y < 0.0f ){
			return false;
		}

		return true;
	}
}