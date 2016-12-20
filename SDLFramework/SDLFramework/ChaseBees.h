#pragma once
#include "IIMkerBehavior.h"
class ChaseBees :
	public ImkerBehavior
{
public:
	ChaseBees(Imker* imker);
	~ChaseBees();

	void checkState(GameController * controller) override;
	void update(GameController* controller) override;
	void Move(GameController* controller) override;

	
};

