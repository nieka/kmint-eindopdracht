#include "CollectPowerUp.h"
#include "GameController.h"
#include <iostream>
#include "PowerMode.h"

class GameController;


CollectPowerUp::CollectPowerUp(Imker* imker)
{
	_imker = imker;
	moveSteps.clear();
}

CollectPowerUp::~CollectPowerUp()
{
}

void CollectPowerUp::checkState(GameController * controller)
{
	Graph* graph = controller->getGrapth();
	if (graph->getImker() == graph->getPowerUp())
	{
		std::cout << "Behavior: Power Mode!" << std::endl;
		graph->setPowerUp(controller->getFacade());
		_imker->deliverbees(controller);
		_imker->setBehavior(new PowerMode(_imker));
	}
}

void CollectPowerUp::update(GameController * controller)
{
}

void CollectPowerUp::Move(GameController* controller)
{
	Graph* graph = controller->getGrapth();
	if (canMove(graph)) {
		if (moveSteps.size() == 0) {
			moveSteps = graph->move(graph->getImker(), graph->getPowerUp());
			graph->setImpkerGoal(graph->getPowerUp());
		}
		else {
			Vertex* loc = moveSteps.at(0);
			loc->setImpker(true);
			graph->setImker(loc);
			moveSteps.erase(moveSteps.begin(), moveSteps.begin() + 1);
		}
	}
	else {
		imkerMovement(*graph);
	}
	
}
