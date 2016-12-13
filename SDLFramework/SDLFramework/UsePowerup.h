#pragma once
#include "IIMkerBehavior.h"
class UsePowerup :
	public ImkerBehavior
{
public:
	UsePowerup(Imker* imker);
	~UsePowerup();

	void checkState() override;
	void update(GameController* controller) override;
};

