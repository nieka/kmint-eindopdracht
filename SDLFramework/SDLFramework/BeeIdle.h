#pragma once
#include "IBeeBehavior.h"
class BeeIdle :
	public IBeeBehavior
{
public:
	BeeIdle(Bee* bee);
	~BeeIdle();

	void checkState() override;
	void update(GameController* controller) override;
}; #pragma once
