#pragma once
#include "IIMkerBehavior.h"
class Panic :
	public ImkerBehavior
{
public:
	Panic(Imker* imker);
	~Panic();

	void checkState() override;
	void update(GameController* controller) override;
};

