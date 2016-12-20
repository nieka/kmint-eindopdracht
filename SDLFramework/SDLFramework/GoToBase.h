#pragma once
#include "IIMkerBehavior.h"
#include "Graph.h"
#include "Imker.h"
#include "GameController.h"

class GoToBase :
	public ImkerBehavior
{
public:
	GoToBase(Imker* imker);
	~GoToBase();

	void checkState(GameController * controller) override;
	void update(GameController* controller) override;
	void Move(GameController* controller) override;
};

