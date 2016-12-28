#pragma once
#include <vector>

class Graph;
class Vertex;
class Imker;
class GameController;
class ImkerBehavior
{
public:
	ImkerBehavior() {};
	~ImkerBehavior() {};

	virtual void checkState(GameController * controller) = 0;
	virtual void update(GameController* controller) = 0;
	virtual void Move(GameController* controller) = 0;

	bool canMove(Graph* graph);
	void imkerMovement(Graph& graph);
protected:
	Imker* _imker;
	std::vector<Vertex*> moveSteps;
};