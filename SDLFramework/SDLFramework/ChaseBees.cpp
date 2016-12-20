#include "ChaseBees.h"
#include <vector>
#include "IGameObject.h"
#include "GameController.h"
#include "Utils.h"
#include "Vector2D.h"
#include "Bee.h"
#include "CollectPowerUp.h"
#include "Panic.h"
#include "GoToBase.h"

class GameController;

ChaseBees::ChaseBees(Imker* imker)
{
	_imker = imker;
}


ChaseBees::~ChaseBees()
{
}

void ChaseBees::checkState(GameController * controller)
{
	if (_imker->getChatchedBees().size() == 10) {
		//verander state
		Utils utils;
		int value = utils.getRandom(0, 100);
		int derde = 100 / 3;
		if (value <= derde) {
			_imker->setBehavior(new CollectPowerUp(_imker));
		}
		else if (value <= derde * 2) {
			_imker->setBehavior(new GoToBase(_imker));
		}
		else {
			_imker->setBehavior(new Panic(_imker));
		}
	}
}

void ChaseBees::update(GameController * controller)
{
	std::vector<IGameObject*> catchedBees;
	Vector2D imkerPos;
	imkerPos.setX(_imker->getX());
	imkerPos.sety(_imker->getY());

	for each (Bee* bee in controller->getGameobjecten())
	{
		if (imkerPos.dist(imkerPos, bee->getPosition()) <= _imker->getCatchRadius() && !bee->isCathced()) {
			bee->setCathced(true);
			_imker->addcatchedBee(bee);
		}
	}

	Graph* graph = controller->getGrapth();

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

void ChaseBees::Move(GameController* controller)
{
	Graph* graph = controller->getGrapth();

}
