#ifndef INCLUDED_RTG_NORMALPLAYER_H
#define INCLUDED_RTG_NORMALPLAYER_H

#include "ResourceHandler.h"

#include "CirclePlayer.h"

namespace RTG
{
	class NormalPlayer : public CirclePlayer
	{
		const float							MOVE_VELOCITY;
		int									m_Energy;
		bool								m_IsReflectMode;
		double								m_ReflectAngle;
		int									m_HPBarTexture;
		int									m_EnergyBarTexture;
		int									m_ReflectModeEffectTexture;
		int									m_PlayerTexture;
	public:
		NormalPlayer( const MAPIL::Vector2 < double >& vPos );
		~NormalPlayer();
		void Draw();
		bool Move();
		void Init();
		bool DoesCollide( const CircleObj& obj );
		bool IsReflectMode() const;
		void DecEnergy( int val );
		void Damage( int val );
		double GetReflectAngle() const;
	};
}

#endif