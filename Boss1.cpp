#include "Boss1.h"
#include "EnemyShot1.h"
#include "Math.h"

namespace RTG
{
	Boss1::Boss1(	CirclePlayer* pPlayer,
					TaskList < CircleEnemyShot >* pList,
					int textureIndex,
					MAPIL::ITexture hpBar ) :	CircleEnemy( pList, MAPIL::Vector2 < double > ( 320.0, 0.0 ), 1.0, MAPIL::DegToRad( 90.0 ), 30, 500, 25000 ),
												m_pPlayer( pPlayer ),
												m_TextureIndex( textureIndex ),
												m_Stage( 0 ),
												m_HPBar( hpBar )
	{
		m_IsBoss = true;
	}

	Boss1::~Boss1()
	{
		m_Stage = 0;
	}

	void Boss1::Draw()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		p->m_Sprite->DrawTexture(	p->m_Texture[ m_TextureIndex ],
									MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE,
									MAPIL::Vector2 < float > (	static_cast < float > ( m_Pos.m_X - p->m_Texture[ m_TextureIndex ]->GetSize().m_X / 2 ),
																static_cast < float > ( m_Pos.m_Y - p->m_Texture[ m_TextureIndex ]->GetSize().m_Y / 2 ) ) );
		// HPÉoÅ[
		MAPIL::Matrix4x4 < float > worldMat;
		MAPIL::Matrix4x4 < float > scaleMat;
		MAPIL::Matrix4x4 < float > posMat;
		float scale = m_HP / 30.0f;
		MAPIL::CreateScalingMat( &scaleMat, scale, 0.2f );
		MAPIL::CreateTranslationMat( &posMat, 1.0f, 50.0f );
		worldMat = scaleMat * posMat;
		p->m_Sprite->DrawTexture( m_HPBar, worldMat );
	}

	bool Boss1::Move()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		

		m_Pos.m_X += m_Speed * cos( m_Angle );
		m_Pos.m_Y += m_Speed * sin( m_Angle );
		++m_Counter;

		// Movement
		if( m_Counter == 120 ){
			m_Speed = 0;
		}


		// Shot
		if( m_Stage == 0 ){
			if( ( m_Counter % 10 ) == 0 ){
				for( int i = 0; i < 36; ++i ){
					double random = Rand(	p->m_RdmSeed.m_PosX,
											p->m_RdmSeed.m_PosY,
											p->m_RdmSeed.m_Score,
											p->m_RdmSeed.m_HitTotal,
											p->m_RdmSeed.m_ReflectTotal,
											p->m_RdmSeed.m_Frame ) * 1.0 / RAND_MAXIMUM;
					m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
														5.0,
														MAPIL::DegToRad( i * 10.0 - 2.0 + 2.0 * random ) + atan2( m_pPlayer->m_Pos.m_Y - m_Pos.m_Y, m_pPlayer->m_Pos.m_X - m_Pos.m_X ),
														5.0 ) );
				}
				p->m_StaticBuf[ 2 ]->Play();
			}
		}
		else if( m_Stage == 1 ){
			if( ( m_Counter % 30 ) <= 15 && ( m_Counter % 2 ) ){
				m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
													6.0,
													atan2( m_pPlayer->m_Pos.m_Y - m_Pos.m_Y, m_pPlayer->m_Pos.m_X - m_Pos.m_X ),
													5.0 ) );
				m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
													6.0,
													MAPIL::DegToRad( 15.0 ) + atan2( m_pPlayer->m_Pos.m_Y - m_Pos.m_Y, m_pPlayer->m_Pos.m_X - m_Pos.m_X ),
													5.0 ) );
				m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
													6.0,
													MAPIL::DegToRad( -15.0 ) + atan2( m_pPlayer->m_Pos.m_Y - m_Pos.m_Y, m_pPlayer->m_Pos.m_X - m_Pos.m_X ),
													5.0 ) );
			}
			if( ( m_Counter % 10 ) == 0 ){
				for( int i = 0; i < 36; ++i ){
					double random = Rand(	p->m_RdmSeed.m_PosX,
											p->m_RdmSeed.m_PosY,
											p->m_RdmSeed.m_Score,
											p->m_RdmSeed.m_HitTotal,
											p->m_RdmSeed.m_ReflectTotal,
											p->m_RdmSeed.m_Frame ) * 1.0 / RAND_MAXIMUM;
					m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
														5.0,
														MAPIL::DegToRad( i * 10.0 - 2.0 + 2.0 * random ) + atan2( m_pPlayer->m_Pos.m_Y - m_Pos.m_Y, m_pPlayer->m_Pos.m_X - m_Pos.m_X ),
														5.0 ) );
				}
				p->m_StaticBuf[ 2 ]->Play();
			}
		}
		else if( m_Stage == 2 ){
			if( ( m_Counter % 150 ) <= 100 ){
				m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
													2.0,
													MAPIL::DegToRad( m_Counter * 10.0 ),
													5.0 ) );
				p->m_StaticBuf[ 2 ]->Play();
			}
			else{
				m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
													5.0,
													MAPIL::DegToRad( ( ( m_Counter % 150 ) - 125 ) * 5.0 ) + atan2( m_pPlayer->m_Pos.m_Y - m_Pos.m_Y, m_pPlayer->m_Pos.m_X - m_Pos.m_X ),
													5.0 ) );
				m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
													5.0,
													MAPIL::DegToRad( ( 125 - ( m_Counter % 150 ) ) * 5.0 ) + atan2( m_pPlayer->m_Pos.m_Y - m_Pos.m_Y, m_pPlayer->m_Pos.m_X - m_Pos.m_X ),
													5.0 ) );
				p->m_StaticBuf[ 2 ]->Play();
			}

			if( ( m_Counter % 300 ) <= 5 ){
				for( int i = 0; i < 30; ++i ){
					double random = Rand(	p->m_RdmSeed.m_PosX,
											p->m_RdmSeed.m_PosY,
											p->m_RdmSeed.m_Score,
											p->m_RdmSeed.m_HitTotal,
											p->m_RdmSeed.m_ReflectTotal,
											p->m_RdmSeed.m_Frame ) * 1.0 / RAND_MAXIMUM;
					m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
														6.0,
														MAPIL::DegToRad( 360.0 * random ),
														5.0 ) );
				}
			}
		}
		else if( m_Stage == 3 ){
			if( ( m_Counter % 60 ) <= 30 && ( m_Counter % 6 ) == 0 ){
				for( int i = 0; i < 6; ++i ){
					for( int j = 0; j < 6; ++j ){
						m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
															1.0 + i * 1.0,
															MAPIL::DegToRad( j * 60.0 ) + atan2( m_pPlayer->m_Pos.m_Y - m_Pos.m_Y, m_pPlayer->m_Pos.m_X - m_Pos.m_X ),
															5.0 ) );
					}
				}
			}

			if( ( m_Counter % 120 ) == 0 ){
				for( int i = 0; i < 36; ++i ){
					double random = Rand(	p->m_RdmSeed.m_PosX,
											p->m_RdmSeed.m_PosY,
											p->m_RdmSeed.m_Score,
											p->m_RdmSeed.m_HitTotal,
											p->m_RdmSeed.m_ReflectTotal,
											p->m_RdmSeed.m_Frame ) * 1.0 / RAND_MAXIMUM;
					m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
														1.0,
														MAPIL::DegToRad( i * 10.0 - 2.0 + 2.0 * random ) + atan2( m_pPlayer->m_Pos.m_Y - m_Pos.m_Y, m_pPlayer->m_Pos.m_X - m_Pos.m_X ),
														5.0 ) );
				}
			}
		}
		else if( m_Stage == 4 ){
			if( ( m_Counter % 120 ) == 0 ){
				for( int j = 0; j < 16; j += 2 ){
					for( int i = 0; i < j; ++i ){
						m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
															5.0 + j * 0.1,
															MAPIL::DegToRad( -6.0 + i * 1.0 ) + atan2( m_pPlayer->m_Pos.m_Y - m_Pos.m_Y, m_pPlayer->m_Pos.m_X - m_Pos.m_X ),
															5.0 ) );
					}
				}
			}
			if( ( m_Counter % 180 ) <= 30 && ( m_Counter % 5 ) == 0 ){
				double random = Rand(	p->m_RdmSeed.m_PosX,
										p->m_RdmSeed.m_PosY,
										p->m_RdmSeed.m_Score,
										p->m_RdmSeed.m_HitTotal,
										p->m_RdmSeed.m_ReflectTotal,
										p->m_RdmSeed.m_Frame ) * 1.0 / RAND_MAXIMUM;
				double offsetAngle = 60.0 * random;
				for( int i = 0; i < 12; ++i ){
					for( int j = 0; j < 6; ++j ){
						m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
															1.0 + i * 0.7,
															MAPIL::DegToRad( j * 60.0 ) + offsetAngle,
															5.0 ) );
					}
				}
			}
		}
		else if( m_Stage == 5 ){
			for( int i = 0; i < 15; ++i ){
				double random = Rand(	p->m_RdmSeed.m_PosX,
										p->m_RdmSeed.m_PosY,
										p->m_RdmSeed.m_Score,
										p->m_RdmSeed.m_HitTotal,
										p->m_RdmSeed.m_ReflectTotal,
										p->m_RdmSeed.m_Frame ) * 1.0 / RAND_MAXIMUM;
				m_pShotList->Add( new EnemyShot1(	MAPIL::Vector2 < double > ( m_Pos.m_X, m_Pos.m_Y ),
													5.0,
													MAPIL::DegToRad( 360.0 * random ),
													5.0 ) );
			}
			p->m_StaticBuf[ 2 ]->Play();
		}

		// Change stage of the boss.
		if( m_HP <= 450 && m_HP >= 350 ){
			m_Stage = 1;
		}
		else if( m_HP < 350 && m_HP >= 250 ){
			m_Stage = 2;
		}
		else if( m_HP < 250 && m_HP >= 150 ){
			m_Stage = 3;
		}
		else if( m_HP < 150 && m_HP >= 50 ){
			m_Stage = 4;
		}
		else if( m_HP < 50 ){
			m_Stage = 5;
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