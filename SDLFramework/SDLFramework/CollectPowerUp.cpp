#include "CollectPowerUp.h"
#include "GameController.h"
#include <iostream>
#include "PowerMode.h"

class GameController;


CollectPowerUp::CollectPowerUp(Imker* imker)
{
	_imker = imker;
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
		_imker->setBehavior(new PowerMode(_imker));
	}
}

void CollectPowerUp::update(GameController * controller)
{
}

void CollectPowerUp::Move(GameController* controller)
{
	Graph* graph = controller->getGrapth();
	graph->move(graph->getImker(), graph->getPowerUp());
}
