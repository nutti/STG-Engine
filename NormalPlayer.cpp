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
		ResourceHandler* p = ResourceHandler::GetInst();

		MAPIL::Matrix4x4 < float > mat;
		MAPIL::Matrix4x4 < float > tmpMat1;
		MAPIL::Matrix4x4 < float > tmpMat2;
		MAPIL::Matrix4x4 < float > tmpMat3;
		MAPIL::CreateTranslationMat(	&tmpMat1,
										static_cast < float > ( - p->m_Texture[ 1 ]->GetSize().m_X / 2 ),
										static_cast < float > ( - p->m_Texture[ 1 ]->GetSize().m_Y / 2 ) );
		MAPIL::CreateRotationZMat( &tmpMat2, static_cast < float > ( m_ReflectAngle - 1.57 ) );
		MAPIL::CreateTranslationMat(	&tmpMat3,
										static_cast < float > ( m_Pos.m_X ),
										static_cast < float > ( m_Pos.m_Y ) );
		mat = tmpMat1 * tmpMat2 * tmpMat3;

		p->m_Sprite->DrawTexture( p->m_Texture[ 1 ], mat );

		if( m_IsReflectMode ){
			MAPIL::Matrix4x4 < float > worldMat;
			MAPIL::Matrix4x4 < float > offsetMat;
			MAPIL::Matrix4x4 < float > scaleMat;
			MAPIL::Matrix4x4 < float > posMat;
			MAPIL::CreateTranslationMat(	&offsetMat,
											static_cast < float > ( - p->m_Texture[ 8 ]->GetSize().m_X / 2 ),
											static_cast < float > ( - p->m_Texture[ 8 ]->GetSize().m_Y / 2 ) );
			float scale = m_Energy / 10000.0f;
			MAPIL::CreateScalingMat( &scaleMat, scale, scale );
			MAPIL::CreateTranslationMat( &posMat, static_cast < float > ( m_Pos.m_X ), static_cast < float > ( m_Pos.m_Y ) );
			worldMat = offsetMat * scaleMat * posMat;
			p->m_Sprite->DrawTexture( p->m_Texture[ 8 ], worldMat );
		}

		// 情報表示
		// エネルギーバー
		MAPIL::Matrix4x4 < float > worldMat;
		MAPIL::Matrix4x4 < float > scaleMat;
		MAPIL::Matrix4x4 < float > posMat;
		float scale = m_Energy / 5000.0f;
		MAPIL::CreateScalingMat( &scaleMat, scale, 0.2f );
		MAPIL::CreateTranslationMat( &posMat, 1.0f, 460.0f );
		worldMat = scaleMat * posMat;
		p->m_Sprite->DrawTexture( m_EnergyBar, worldMat );
		// HPバー
		scale = m_HP / 25.0f;
		MAPIL::CreateScalingMat( &scaleMat, scale, 0.2f );
		MAPIL::CreateTranslationMat( &posMat, 1.0f, 450.0f );
		worldMat = scaleMat * posMat;
		p->m_Sprite->DrawTexture( m_HPBar, worldMat );
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