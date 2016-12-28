#pragma once
#include "IIMkerBehavior.h"
#include "Graph.h"
#include "Imker.h"
#include "GameController.h"

class GoToBase :
	public ImkerBehavior
{
public:
	GoToBase(Imker* imker, std::string laststate);
	~GoToBase();

	void checkState(GameController * controller) override;
	void update(GameController* controller) override;
	void Move(GameController* controller) override;
	void reflection();
private:
	std::string _lastState;
};

