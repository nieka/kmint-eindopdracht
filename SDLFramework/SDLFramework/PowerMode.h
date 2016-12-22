#pragma once
#include "IIMkerBehavior.h"
#include "Utils.h"

class PowerMode :
	public ImkerBehavior
{
public:
	PowerMode(Imker* imker);
	~PowerMode();

	void checkState(GameController * controller) override;
	void update(GameController* controller) override;
	void Move(GameController* controller) override;

private:
	Utils utils;
};