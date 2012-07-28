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

	void ResetRandSeed()
	{
		g_RandCount = 0;
	}
}