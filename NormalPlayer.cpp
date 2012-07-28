#include "NormalPlayer.h"

#include "Score.h"
#include "GeneralButtonManager.h"

namespace RTG
{
	NormalPlayer::NormalPlayer( const MAPIL::Vector2 < double >& vPos,
								MAPIL::ITexture energyBar,
								MAPIL::ITexture hpBar ) :	CirclePlayer( vPos, 3.0f ),
																			MOVE_VELOCITY( 3.0f ),
																			m_Energy( 20000 ),
																			m_IsReflectMode( false ),
																			m_ReflectAngle( 0.0 ),
																			m_EnergyBar( energyBar ),
																			m_HPBar( hpBar )
	{
		m_HP = 100;
	}

	NormalPlayer::~NormalPlayer()
	{
		m_Energy = 0;
		m_IsReflectMode = false;
		m_ReflectAngle = 0.0;
	}

	void NormalPlayer::Draw()
	{

		MAPIL::DrawTexture( 1, m_Pos.m_X, m_Pos.m_Y, m_ReflectAngle );


		if( m_IsReflectMode ){
			float scale = m_Energy / 10000.0f;
			MAPIL::DrawTexture( 0, m_Pos.m_X, m_Pos.m_Y, 0.0f );
		}

		// 情報表示
		// エネルギーバー
		float scale = m_Energy / 5000.0f;
		//MAPIL::CreateScalingMat( &scaleMat, scale, 0.2f );
		MAPIL::DrawTexture( 0, 1.0f, 460.0f, 0.0f );
		// HPバー
		//scale = m_HP / 25.0f;
		//MAPIL::CreateScalingMat( &scaleMat, scale, 0.2f );
		MAPIL::DrawTexture( 0, 1.0f, 450.0f, 0.0f );
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
}