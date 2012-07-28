#include "MenuEffect1.h"
#include "ResourceHandler.h"



namespace RTG
{
	float CreateRandNum()
	{
		return 0.2f + 0.8f * rand() / RAND_MAX;
	}

	MenuEffect1::MenuEffect1(	MAPIL::IPointSprite sprite,
								MAPIL::Vector3 < float > pos,
								double speed,
								double angle,
								int index ) :	Effect3D(),
												m_Counter( 0 ),
												m_Pos( pos ),
												m_Speed( speed ),
												m_Angle( angle ),
												m_Index( index ),
												m_Sprite( sprite ),
												//m_Color( MAPIL::ColorARGB < float > ( 1.0f, 1.0f, 1.0f, 1.0f ) )
												m_Color( MAPIL::ColorARGB < float > ( 1.0f, CreateRandNum(), CreateRandNum(), CreateRandNum() ) )
	{
	}

	MenuEffect1::~MenuEffect1()
	{
		m_Counter = 0;
		m_Speed = 0.0;
		m_Angle = 0;
	}

	void MenuEffect1::Draw()
	{
	}

	bool MenuEffect1::Move()
	{
		m_Pos.m_X += static_cast < float > ( m_Speed * cos( m_Angle ) );
		m_Pos.m_Y += static_cast < float > ( m_Speed * sin( m_Angle ) );
		++m_Counter;

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

		m_Sprite->Update( m_Index, m_Pos, 1.0f, m_Color );

		return true;
	}

	int MenuEffect1::GetIndex() const
	{
		return m_Index;
	}
}