#include "MAPILString.h"
#include "ResourceHandler.h"

namespace RTG
{


	MAPILString::MAPILString()
	{
		ResourceHandler* p = ResourceHandler::GetInst();
		MAPIL::CreateSplitedTexture( m_Textures, p->m_Archiver, "archive/resource/texture/Score.png", 1, 16, 16, 16 );
	}

	MAPILString::~MAPILString()
	{
	}

	void MAPILString::Display( char c, float x, float y ) const
	{
		//MAPIL::BeginRendering2DGraphics();
		//MAPIL::DrawString( x, y, "%c", c );
		//MAPIL::EndRendering2DGraphics();
		if( c >= '0' && c <= '9' ){
			MAPIL::BeginRendering2DGraphics();
			MAPIL::DrawTexture( m_Textures[ c - '0' ], x, y, 1.0f, 1.0f, 0.0f );
			MAPIL::EndRendering2DGraphics();
			//m_Texture->SetSplitIndex( c - '0' );
			//m_Sprite->DrawTexture(	m_Texture,
			//						MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE,
			//						MAPIL::Vector2 < float > ( x, y ) );
		}
	}
}