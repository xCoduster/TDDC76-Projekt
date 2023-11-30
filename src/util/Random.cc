#include "Random.h"

#include <random>

int random(int min, int max)
{
	int range = max - min + 1;

	if (range == 0)
		return 0;

	return min + std::rand() % range;
}