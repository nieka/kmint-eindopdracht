#pragma once

class Bee;
class GameController;
class IBeeBehavior
{
public:
	IBeeBehavior() {};
	~IBeeBehavior() {};

	virtual void checkState() = 0;
	virtual void update(GameController* controller) = 0;

protected:
	Bee* _bee;
};