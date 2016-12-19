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

	if (_imker->getX() < graph->getImker()->getX())
	{
		_imker->setX(_imker->getX() + 1);
	}
	else if (_imker->getX() > graph->getImker()->getX())
	{
		_imker->setX(_imker->getX() - 1);
	}

	if (_imker->getY() < graph->getImker()->getY())
	{
		_imker->setY(_imker->getY() + 1);
	}
	else if (_imker->getY() > graph->getImker()->getY())
	{
		_imker->setY(_imker->getY() - 1);
	}
}

void CollectPowerUp::Move(GameController* controller)
{
	Graph* graph = controller->getGrapth();
	graph->move(graph->getImker(), graph->getPowerUp());
}
