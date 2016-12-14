#pragma once
#include "IBeeBehavior.h"
class BeeFlee :
	public IBeeBehavior
{
public:
	BeeFlee(Bee* bee);
	~BeeFlee();

	void checkState() override;
	void update(GameController* controller) override;
};