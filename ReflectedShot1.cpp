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

		p->m_Sprite->DrawTexture(	p->m_Texture[ m_TextureIndex ],
									MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE,
									MAPIL::Vector2 < float > (	static_cast < float > ( m_Pos.m_X - p->m_Texture[ m_TextureIndex ]->GetSize().m_X / 2 ),
																static_cast < float > ( m_Pos.m_Y - p->m_Texture[ m_TextureIndex ]->GetSize().m_Y / 2 ) ) );
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