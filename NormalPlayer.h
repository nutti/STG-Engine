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
		MAPIL::ITexture						m_EnergyBar;
		MAPIL::ITexture						m_HPBar;
	public:
		NormalPlayer(	const MAPIL::Vector2 < double >& vPos,
						MAPIL::ITexture energyBar,
						MAPIL::ITexture hpBar );
		~NormalPlayer();
		void Draw();
		bool Move();
		bool DoesCollide( const CircleObj& obj );
		bool IsReflectMode() const;
		void DecEnergy( int val );
		void Damage( int val );
		double GetReflectAngle() const;
	};
}

#endif