#include "NormalPlayer.h"

#include "Score.h"
#include "GeneralButtonManager.h"

namespace RTG
{
	NormalPlayer::NormalPlayer( const MAPIL::Vector2 < double >& vPos ) :	CirclePlayer( vPos, 3.0f ),
																			MOVE_VELOCITY( 3.0f ),
																			m_Energy( 20000 ),
																			m_IsReflectMode( false ),
																			m_ReflectAngle( 0.0 )
	{
		m_HP = 100;
	}

	NormalPlayer::~NormalPlayer()
	{
		m_Energy = 0;
		m_IsReflectMode = false;
		m_ReflectAngle = 0.0;
		MAPIL::DeleteTexture( m_HPBarTexture );
		MAPIL::DeleteTexture( m_EnergyBarTexture );
		MAPIL::DeleteTexture( m_PlayerTexture );
		MAPIL::DeleteTexture( m_ReflectModeEffectTexture );
	}

	void NormalPlayer::Draw()
	{

		MAPIL::DrawTexture( m_PlayerTexture, m_Pos.m_X, m_Pos.m_Y, m_ReflectAngle - 1.57 );


		if( m_IsReflectMode ){
			float scale = m_Energy / 10000.0f;
			MAPIL::DrawTexture( m_ReflectModeEffectTexture, m_Pos.m_X, m_Pos.m_Y, scale, scale, 0.0f );
		}

		// 情報表示
		// エネルギーバー
		MAPIL::DrawTextureNonCentering( m_EnergyBarTexture, 10.0f, 460.0f, m_Energy / 5000.0f, 0.2f, 0.0f );
		// HPバー
		MAPIL::DrawTextureNonCentering( m_HPBarTexture, 10.0f, 450.0f, m_HP / 25.0f, 0.2f, 0.0f );
	}

	bool NormalPlayer::Move()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		bool hasMoved = false;

		p->m_pGBManager->IsPushed( GENERAL_BUTTON_LEFT );

		if( p->m_pGBManager->IsPushed( GENERAL_BUTTON_LEFT ) ){
			m_Pos.m_X -= MOVE_VELOCITY;
			hasMoved = true;
		}
		if( p->m_pGBManager->IsPushed( GENERAL_BUTTON_RIGHT ) ){
			m_Pos.m_X += MOVE_VELOCITY;
			hasMoved = true;
		}
		if( p->m_pGBManager->IsPushed( GENERAL_BUTTON_UP ) ){
			m_Pos.m_Y -= MOVE_VELOCITY;
			hasMoved = true;
		}
		if( p->m_pGBManager->IsPushed( GENERAL_BUTTON_DOWN ) ){
			m_Pos.m_Y += MOVE_VELOCITY;
			hasMoved = true;
		}
		if( p->m_pGBManager->IsPushed( GENERAL_BUTTON_ROT_CCW ) ){
			m_ReflectAngle += 0.05;
			if( m_ReflectAngle >= 6.28 ){
				m_ReflectAngle = 0.001;
			}
		}
		if( p->m_pGBManager->IsPushed( GENERAL_BUTTON_ROT_CW ) ){
			m_ReflectAngle -= 0.05;
			if( m_ReflectAngle <= 0.0 ){
				m_ReflectAngle = 6.279;
			}
		}

		if( m_Pos.m_X > 640.0 ){
			m_Pos.m_X = 640.0;
		}
		if( m_Pos.m_Y > 480.0 ){
			m_Pos.m_Y = 480.0;
		}
		if( m_Pos.m_X < 0.0 ){
			m_Pos.m_X = 0.0;
		}
		if( m_Pos.m_Y < 0.0 ){
			m_Pos.m_Y = 0.0;
		}

		if( m_IsReflectMode ){
			if( hasMoved ){
				m_Energy -= 3;
			}
			else{
				--m_Energy;
			}
		}
		else{
			if( hasMoved ){
				m_Energy += 4;
			}
			else{
				m_Energy += 10;
			}
		}

		if( m_Energy > 100 && p->m_pGBManager->IsPushed( GENERAL_BUTTON_BARRIER ) ){
			m_IsReflectMode = true;
		}
		else{
			m_IsReflectMode = false;
		}

		if( m_Energy >= 20000 ){
			m_Energy = 20000;
		}

		++m_Counter;

		if( m_HP <= 0 ){
			return false;
		}

		return true;
	}

	bool NormalPlayer::DoesCollide( const CircleObj& obj )
	{
		MAPIL::Vector2 < double > diff = m_Pos - obj.m_Pos;
		if( diff.GetNorm() < obj.m_Radius + m_Radius ){
			return true;
		}

		return false;
	}

	bool NormalPlayer::IsReflectMode() const
	{
		return m_IsReflectMode;
	}

	void NormalPlayer::DecEnergy( int val )
	{
		m_Energy -= val;
	}

	void NormalPlayer::Damage( int val )
	{
		m_HP -= val;
	}

	double NormalPlayer::GetReflectAngle() const
	{
		return m_ReflectAngle;
	}

	void NormalPlayer::Init()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		m_EnergyBarTexture = MAPIL::CreateTexture( p->m_Archiver, "archive/resource/texture/EnergyBar.png" );
		m_HPBarTexture = MAPIL::CreateTexture( p->m_Archiver, "archive/resource/texture/HPBar.png" );
		m_ReflectModeEffectTexture = MAPIL::CreateTexture( p->m_Archiver, "archive/resource/texture/ReflectModeEffect.png" );
		m_PlayerTexture = MAPIL::CreateTexture( p->m_Archiver, "archive/resource/texture/NormalPlayer.png" );
	}
}