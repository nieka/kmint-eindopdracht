#pragma once
#include "IIMkerBehavior.h"
#include "Utils.h"
#include "Vertex.h"

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
	Vertex* _targetPos = nullptr;
};

