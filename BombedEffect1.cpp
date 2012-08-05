#include "BombedEffect1.h"

#include "ResourceHandler.h"

namespace RTG
{
	BombedEffect1::BombedEffect1(	MAPIL::Vector2 < float >& vPos,
									float radius,
									double speed,
									int imgID ) :	Effect2D(),
													m_Pos( vPos ),
													m_Radius( radius ),
													m_Speed( speed ),
													m_ImgID( imgID )
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
		ResourceHandler* p = ResourceHandler::GetInst();

		MAPIL::DrawTexture( p->GetTextureHandle( m_ImgID ), m_Pos.m_X, m_Pos.m_Y, m_Radius, m_Radius, 0.0f );
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