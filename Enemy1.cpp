#include "Enemy1.h"
#include "EnemyShot1.h"
#include "Math.h"

namespace RTG
{
	Enemy1::Enemy1(	CirclePlayer* pPlayer,
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

	Enemy1::~Enemy1()
	{
	}

	void Enemy1::Draw()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		p->m_Sprite->DrawTexture(	p->m_Texture[ m_TextureIndex ],
									MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE,
									MAPIL::Vector2 < float > (	static_cast < float > ( m_Pos.m_X - p->m_Texture[ m_TextureIndex ]->GetSize().m_X / 2 ),
																static_cast < float > ( m_Pos.m_Y - p->m_Texture[ m_TextureIndex ]->GetSize().m_Y / 2 ) ) );
	}

	bool Enemy1::Move()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		m_Pos.m_X += m_Speed * cos( m_Angle );
		m_Pos.m_Y += m_Speed * sin( m_Angle );
		++m_Counter;

		if( !( m_Counter % 20 ) && m_Counter >= 20 && m_Counter <= 140 ){
			double random = Rand(	p->m_RdmSeed.m_PosX,
									p->m_RdmSeed.m_PosY,
									p->m_RdmSeed.m_Score,
									p->m_RdmSeed.m_HitTotal,
									p->m_RdmSeed.m_ReflectTotal,
									p->m_RdmSeed.m_Frame ) * 1.0 / RAND_MAXIMUM;
			m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
												4.5,
												MAPIL::DegToRad( -3.5 + 7.0 * random ) + atan2( m_pPlayer->m_Pos.m_Y - m_Pos.m_Y, m_pPlayer->m_Pos.m_X - m_Pos.m_X ),
												5.0 ) );
			p->m_StaticBuf[ 2 ]->Play();
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