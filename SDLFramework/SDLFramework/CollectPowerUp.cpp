#include "CollectPowerUp.h"
#include "GameController.h"
#include <iostream>

class GameController;


CollectPowerUp::CollectPowerUp(Imker* imker)
{
	_imker = imker;
}


CollectPowerUp::~CollectPowerUp()
{
}

void CollectPowerUp::checkState()
{
}

void CollectPowerUp::update(GameController * controller)
{
	Graph* graph = controller->getGrapth();
	if (graph->getImker() == graph->getPowerUp())
	{
		std::cout<< "de imker heeft de powerup gevonden" << std::endl;
	}
}

void CollectPowerUp::Move(GameController* controller)
{
	Graph* graph = controller->getGrapth();
	graph->move(graph->getImker(), graph->getPowerUp());
}
