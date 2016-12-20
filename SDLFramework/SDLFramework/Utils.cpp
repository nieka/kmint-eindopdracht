#include "Utils.h"
#include <random>

Utils::Utils()
{
}


Utils::~Utils()
{
}

int Utils::min(int minvalue, int value)
{
	if (value < minvalue) {
		return minvalue;
	}
	else {
		return value;
	}
}

int Utils::max(int maxvalue, int value)
{
	if (value > maxvalue) {
		return maxvalue;
	}
	else {
		return value;
	}
}

int Utils::getRandom(int min, int max)
{
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

	return uni(rng);

}
