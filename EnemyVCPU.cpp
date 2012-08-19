#include "EnemyVCPU.h"

#include "EnemyShot1.h"
#include "BombedEffect1.h"

#include "Math.h"

namespace RTG
{
	EnemyVCPU::EnemyVCPU() : VM::VCPU()
	{
	}

	EnemyVCPU::~EnemyVCPU()
	{
	}

	void EnemyVCPU::Init( VM::Data* pData, EnemyInfo* pInfo )
	{
		m_pData = pData;
		m_pEnemyInfo = pInfo;
		VM::VCPU::Init();
	}

	void EnemyVCPU::SysGetEnemyPosX()
	{
		Pop();
		Push( m_pEnemyInfo->m_PosX );
	}

	void EnemyVCPU::SysGetEnemyPosY()
	{
		Pop();
		Push( m_pEnemyInfo->m_PosY );
	}

	void EnemyVCPU::SysGetEnemyHP()
	{
		Pop();
		Push( m_pEnemyInfo->m_HP );
	}

	void EnemyVCPU::SysGetEnemySpeed()
	{
		Pop();
		Push( (int)m_pEnemyInfo->m_Speed );
	}

	void EnemyVCPU::SysGetEnemyCounter()
	{
		Pop();
		Push( m_pEnemyInfo->m_Counter );
	}

	void EnemyVCPU::SysGetEnemyCounterF()
	{
		Pop();
		Push( VM::Value( static_cast < float > ( m_pEnemyInfo->m_Counter ) ) );
	}

	void EnemyVCPU::SysGetEnemyAngle()
	{
		Pop();
		Push( (int)m_pEnemyInfo->m_Angle );
	}

	void EnemyVCPU::SysSetEnemyPos()
	{
		Pop();
		float y = Top().m_Float;
		Pop();
		float x = Top().m_Float;
		Pop();
		m_pEnemyInfo->m_PosX = x;
		m_pEnemyInfo->m_PosY = y;
	}

	void EnemyVCPU::SysSetEnemyAngle()
	{
		Pop();
		int angle = Top().m_Integer;
		Pop();
		m_pEnemyInfo->m_Angle = angle;
	}

	void EnemyVCPU::SysSetEnemySpeed()
	{
		Pop();
		int speed = Top().m_Integer;
		Pop();
		m_pEnemyInfo->m_Speed = speed;
	}

	void EnemyVCPU::SysSetEnemyHP()
	{
		Pop();
		int hp = Top().m_Integer;
		Pop();
		m_pEnemyInfo->m_HP = hp;
	}

	void EnemyVCPU::SysSetEnemyImgID()
	{
		Pop();
		int id = Top().m_Integer;
		Pop();
		m_pEnemyInfo->m_ImgID = id;
	}

	void EnemyVCPU::SysSetEnemyCollisionRadius()
	{
		Pop();
		float radius = Top().m_Float;
		Pop();
		m_pEnemyInfo->m_ColRadius = radius;
	}

	void EnemyVCPU::SysSetEnemyScore()
	{
		Pop();
		int score = Top().m_Integer;
		Pop();
		m_pEnemyInfo->m_Score = score;
	}

	void EnemyVCPU::SysSetEnemyBossFlag()
	{
		Pop();
		int flag = Top().m_Integer;
		Pop();
		m_pEnemyInfo->m_IsBoss = flag;
	}

	void EnemyVCPU::SysCreateEnemyShot1()
	{
		Pop();
		int imgID = Top().m_Integer;
		Pop();
		float radius = Top().m_Float;
		Pop();
		float angle = Top().m_Float;
		Pop();
		float speed = Top().m_Float;
		Pop();
		float y = Top().m_Float;
		Pop();
		float x = Top().m_Float;
		Pop();
		m_pEnemyInfo->m_pShotList->Add( new EnemyShot1( MAPIL::Vector2 < double > ( x, y ), speed, angle, radius, imgID ) );
	}

	void EnemyVCPU::SysGetPlayerPosX()
	{
		Pop();

		TaskList < CirclePlayer >::Iterator it( m_pEnemyInfo->m_pPlayerList );
		TaskList < CirclePlayer >::Iterator itEnd( m_pEnemyInfo->m_pPlayerList );
		itEnd.End();

		float result = 0.0f;

		// プレイヤーの情報の更新
		for( it.Begin(); it != itEnd; ++it ){
			result = ( *it ).GetPos().m_X;
		}

		Push( result );
	}

	void EnemyVCPU::SysGetPlayerPosY()
	{
		Pop();

		TaskList < CirclePlayer >::Iterator it( m_pEnemyInfo->m_pPlayerList );
		TaskList < CirclePlayer >::Iterator itEnd( m_pEnemyInfo->m_pPlayerList );
		itEnd.End();

		float result = 0.0f;

		// プレイヤーの情報の更新
		for( it.Begin(); it != itEnd; ++itEnd ){
			result = ( *it ).GetPos().m_Y;
		}

		Push( result );
	}

	void EnemyVCPU::SysGetRandF()
	{
		Pop();

		Push( Rand() * 1.0f / RAND_MAXIMUM );
	}

	void EnemyVCPU::SysCreateEffect1()
	{
		Pop();

		int id = Top().m_Integer;
		Pop();
		float y = Top().m_Float;
		Pop();
		float x = Top().m_Float;
		Pop();

		m_pEnemyInfo->m_pEffect2DList->Add( new BombedEffect1( MAPIL::Vector2 < float > ( x, y ), 0.1f, 0.2f, id ) );
	}

	void EnemyVCPU::OpSysCall( int val )
	{
		switch( val ){
			case VM::SYS_GET_RANDOM_F:
				SysGetRandF();
				break;
			case VM::SYS_GET_PLAYER_POSX:
				SysGetPlayerPosX();
				break;
			case VM::SYS_GET_PLAYER_POSY:
				SysGetPlayerPosY();
				break;
			case VM::SYS_ENEMY_GET_POSX:
				SysGetEnemyPosX();
				break;
			case VM::SYS_ENEMY_GET_POSY:
				SysGetEnemyPosY();
				break;
			case VM::SYS_ENEMY_GET_HP:
				SysGetEnemyHP();
				break;
			case VM::SYS_ENEMY_GET_SPEED:
				SysGetEnemySpeed();
				break;
			case VM::SYS_ENEMY_GET_COUNTER:
				SysGetEnemyCounter();
				break;
			case VM::SYS_ENEMY_GET_COUNTER_F:
				SysGetEnemyCounterF();
				break;
			case VM::SYS_ENEMY_SET_POS:
				SysSetEnemyPos();
				break;
			case VM::SYS_ENEMY_SET_ANGLE:
				SysSetEnemyAngle();
				break;
			case VM::SYS_ENEMY_SET_SPEED:
				SysSetEnemySpeed();
				break;
			case VM::SYS_ENEMY_SET_HP:
				SysSetEnemyHP();
				break;
			case VM::SYS_ENEMY_CREATE_SHOT_1:
				SysCreateEnemyShot1();
				break;
			case VM::SYS_ENEMY_SET_IMAGE:
				SysSetEnemyImgID();
				break;
			case VM::SYS_ENEMY_SET_COLLISION_RADIUS:
				SysSetEnemyCollisionRadius();
				break;
			case VM::SYS_ENEMY_SET_SCORE:
				SysSetEnemyScore();
				break;
			case VM::SYS_ENEMY_SET_BOSS_FLAG:
				SysSetEnemyBossFlag();
				break;
			case VM::SYS_ENEMY_CREATE_EFFECT_1:
				SysCreateEffect1();
				break;
			default:
				VM::VCPU::OpSysCall( val );
				break;
		}
	}
}