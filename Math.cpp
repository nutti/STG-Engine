#include "ResourceHandler.h"

#include "Math.h"

namespace RTG
{
	int g_RandCount = 0;
	static const int RAND_SEED = 47;

	int Rand( int posX, int posY, int score, int hitTotal, int reflectTotal, int frame )
	{
		++g_RandCount;
		return ( ( posX + hitTotal + score + reflectTotal + frame + g_RandCount * RAND_SEED ) * ( frame + g_RandCount + score * posY ) ) % RAND_MAXIMUM;
	}

	int Rand()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		return Rand(	p->m_RdmSeed.m_PosX,
						p->m_RdmSeed.m_PosY,
						p->m_RdmSeed.m_Score,
						p->m_RdmSeed.m_HitTotal,
						p->m_RdmSeed.m_ReflectTotal,
						p->m_RdmSeed.m_Frame );
	}

	void ResetRandSeed()
	{
		g_RandCount = 0;
	}
}