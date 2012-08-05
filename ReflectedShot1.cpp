#include "ReflectedShot1.h"

#include "ResourceHandler.h"

namespace RTG
{
	ReflectedShot1::ReflectedShot1(	const CircleEnemyShot& shot,
									const NormalPlayer& player,
									int textureIndex ) :	CircleReflectedShot(	shot.m_Pos,
																					shot.m_Speed,
																					-player.GetReflectAngle(),
																					3.0 ),
															m_TextureIndex( textureIndex )
	{
	}

	ReflectedShot1::~ReflectedShot1()
	{
	}
	void ReflectedShot1::Draw()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		MAPIL::DrawTexture(	p->GetTextureHandle( m_TextureIndex ),
							m_Pos.m_X, m_Pos.m_Y, 0.0f,
							0xFF7FFFD4 );
	}

	bool ReflectedShot1::Move()
	{
		m_Pos.m_X += m_Speed * cos( m_Angle );
		m_Pos.m_Y += m_Speed * sin( m_Angle );

		++m_Counter;

		if( m_Pos.m_X > 640.0f || m_Pos.m_X < 0.0f || m_Pos.m_Y > 480.0f || m_Pos.m_Y < 0.0f ){
			return false;
		}

		return true;
	}

}