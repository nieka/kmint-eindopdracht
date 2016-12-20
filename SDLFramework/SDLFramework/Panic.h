#pragma once
#include "IIMkerBehavior.h"
#include "Utils.h"

class Panic :
	public ImkerBehavior
{
public:
	Panic(Imker* imker);
	~Panic();

	void checkState(GameController * controller) override;
	void update(GameController* controller) override;
	void Move(GameController* controller) override;

private:
	Utils utils;
};

