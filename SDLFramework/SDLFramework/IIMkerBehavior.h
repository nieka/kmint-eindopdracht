#pragma once

class Imker;
class GameController;
class ImkerBehavior
{
public:
	ImkerBehavior() {};
	~ImkerBehavior() {};

	virtual void checkState() = 0;
	virtual void update(GameController* controller) = 0;

protected:
	Imker* _imker;
};