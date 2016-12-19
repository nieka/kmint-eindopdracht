#pragma once
#include "IIMkerBehavior.h"
class CollectPowerUp :
	public ImkerBehavior
{
public:
	CollectPowerUp(Imker* imker);
	~CollectPowerUp();

	void checkState() override;
	void update(GameController* controller) override;
	void Move(GameController* controller) override;
};

