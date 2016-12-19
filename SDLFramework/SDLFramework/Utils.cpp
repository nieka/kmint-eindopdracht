#include "Utils.h"



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
