#pragma once
#include "IIMkerBehavior.h"
class CollectPowerUp :
	public ImkerBehavior
{
public:
	CollectPowerUp(Imker* imker);
	~CollectPowerUp();

	void checkState(GameController * controller) override;
	void update(GameController* controller) override;
	void Move(GameController* controller) override;
};

