#include "Stage1Effect1.h"
#include "ResourceHandler.h"



namespace RTG
{

	Stage1Effect1::Stage1Effect1(	int sprite,
								MAPIL::Vector3 < float > pos,
								double speed,
								double angle,
								int index ) :	Effect3D(),
												m_Counter( 0 ),
												m_Pos( pos ),
												m_Speed( speed ),
												m_Angle( angle ),
												m_Index( index ),
												m_PSprite( sprite ),
												//m_Color( MAPIL::ColorARGB < float > ( 1.0f, 1.0f, 1.0f, 1.0f ) )
												m_Color( MAPIL::ColorARGB < float > ( 1.0f, 0.5f, 0.5f, 0.5f ) )
	{
	}

	Stage1Effect1::~Stage1Effect1()
	{
		m_Counter = 0;
		m_Speed = 0.0;
		m_Angle = 0;
	}

	void Stage1Effect1::Draw()
	{
	}

	bool Stage1Effect1::Move()
	{
		m_Pos.m_X += static_cast < float > ( m_Speed * cos( m_Angle ) );
		m_Pos.m_Y += static_cast < float > ( m_Speed * sin( m_Angle ) );
		++m_Counter;

		if( m_Pos.m_X > 20.0 ){
			return false;
		}
		if( m_Pos.m_X < -20.0 ){
			return false;
		}
		if( m_Pos.m_Y < -20.0 ){
			return false;
		}
		if( m_Pos.m_Y > 20.0 ){
			return false;
		}

		MAPIL::UpdatePointSprite(	m_PSprite, m_Index, m_Pos, 1.0f,
									MAPIL::GetColorARGBValue( m_Color.m_A, m_Color.m_R, m_Color.m_G, m_Color.m_B ) );

		return true;
	}

	int Stage1Effect1::GetIndex() const
	{
		return m_Index;
	}
}