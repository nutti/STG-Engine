#include "BombedEffect1.h"

namespace RTG
{
	BombedEffect1::BombedEffect1(	MAPIL::ISprite sprite,
									MAPIL::ITexture texture,
									MAPIL::Vector2 < float >& vPos,
									float radius,
									double speed ) :	Effect2D(),
															m_Sprite( sprite ),
															m_Texture( texture ),
															m_Pos( vPos ),
															m_Radius( radius ),
															m_Speed( speed )
	{
	}

	BombedEffect1::~BombedEffect1()
	{
		m_Radius = 0.0f;
		m_Speed = 0.0f;
	}

	bool BombedEffect1::Update()
	{
		bool ret = Move();

		Draw();
		
		return ret;
	}

	void BombedEffect1::Draw()
	{
		MAPIL::Matrix4x4 < float > transMat;
		MAPIL::Matrix4x4 < float > m1;
		MAPIL::Matrix4x4 < float > m2;
		MAPIL::Matrix4x4 < float > m3;

		MAPIL::CreateTranslationMat( &m1, -m_Texture->GetSize().m_X / 2.0f, -m_Texture->GetSize().m_Y / 2.0f );
		MAPIL::CreateScalingMat( &m2, m_Radius, m_Radius );
		MAPIL::CreateTranslationMat( &m3, m_Pos.m_X, m_Pos.m_Y );
		transMat = m1 * m2 * m3;

		m_Sprite->DrawTexture( m_Texture, transMat );
	}

	bool BombedEffect1::Move()
	{
		if( m_Radius >= 2.0f ){
			return false;
		}

		m_Radius += m_Speed;

		return true;
	}
}