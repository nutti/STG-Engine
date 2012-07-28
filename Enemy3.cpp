#include "Enemy3.h"
#include "EnemyShot1.h"

namespace RTG
{

	Enemy3::Enemy3(	CirclePlayer* pPlayer,
					TaskList < CircleEnemyShot >* pList,
					MAPIL::Vector2 < double >& vPos,
					double speed,
					double angle,
					double radius,
					int hp,
					int textureIndex,
					int score ) :	CircleEnemy( pList, vPos, speed, angle, radius, hp, score ),
									m_pPlayer( pPlayer ),
									m_TextureIndex( textureIndex )
	{
	}

	Enemy3::~Enemy3()
	{
		m_TextureIndex = 0;
	}

	void Enemy3::Draw()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		p->m_Sprite->DrawTexture(	p->m_Texture[ m_TextureIndex ],
									MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE,
									MAPIL::Vector2 < float > (	static_cast < float > ( m_Pos.m_X - p->m_Texture[ m_TextureIndex ]->GetSize().m_X / 2 ),
																static_cast < float > ( m_Pos.m_Y - p->m_Texture[ m_TextureIndex ]->GetSize().m_Y / 2 ) ) );
	}

	bool Enemy3::Move()
	{
		m_Pos.m_X += m_Speed * cos( m_Angle );
		m_Pos.m_Y += m_Speed * sin( m_Angle );
		++m_Counter;

		if( m_Counter < 250 && m_Counter > 80 ){
			ResourceHandler* p = ResourceHandler::GetInst();
			float angle1 = static_cast < float > ( MAPIL::DegToRad( m_Counter * 7.0 ) );
			float angle2 = static_cast < float > ( - MAPIL::DegToRad( m_Counter * 5.0 ) );
			m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
												3.0,
												angle1,
												5.0 ) );
			m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
												3.0,
												angle2,
												5.0 ) );
			p->m_StaticBuf[ 2 ]->Play();
		}

		if( m_Counter >= 60 ){
			m_Speed = 0;
		}

		if( m_Counter >= 260 ){
			m_Speed = 1.0;
			m_Angle = MAPIL::DegToRad( 10.0 );
		}

		if( m_Pos.m_X > 660.0 ){
			return false;
		}
		if( m_Pos.m_X < -20.0 ){
			return false;
		}
		if( m_Pos.m_Y < -20.0 ){
			return false;
		}
		if( m_Pos.m_Y > 500.0 ){
			return false;
		}

		if( m_HP <= 0 ){
			return false;
		}

		return true;
	}
}