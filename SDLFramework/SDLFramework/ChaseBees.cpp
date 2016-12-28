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
#include "string"
#include "Iostream"

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
	if (_imker->getChatchedBees().size() >= 10 || _imker->CatchedAllBees(controller)) {
		//verander state
		Utils utils;

		if (_imker->CatchedAllBees(controller))
		{
			_imker->setBehavior(new GoToBase(_imker, "chasebees"));
		}
		else
		{
			int value = utils.getRandom(0, 100);
			if (value <= _imker->getCollectPowerUp()) {
				std::cout << "behaviour: Collect Power up" << std::endl;
				_imker->setBehavior(new CollectPowerUp(_imker));
			}
			else if (value <= _imker->getReturnToBase()) {
				std::cout << "behaviour: Go to Base" << std::endl;
				_imker->setBehavior(new GoToBase(_imker, "chasebees"));
			}
			else {
				std::cout << "behaviour: Panic" << std::endl;
				_imker->setBehavior(new Panic(_imker));
			}
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
		if (imkerPos.dist(imkerPos, bee->getPosition()) <= _imker->getCatchRadius() && !bee->isCathced() && _imker->getChatchedBees().size() <= 10) {
			bee->setCathced(true);
			_imker->addcatchedBee(bee);
			std::cout << "Catched a bee" << std::endl;
			std::cout << "Bee's: " << std::to_string(_imker->getChatchedBees().size()) << std::endl;
		}
	}
}

void ChaseBees::Move(GameController* controller)
{
	Graph* graph = controller->getGrapth();
	if (_targetPos == graph->getImker() || _targetPos == nullptr) {
		Vector2D imkerPos;
		imkerPos.setX(_imker->getX());
		imkerPos.sety(_imker->getY());
		Bee* target = dynamic_cast<Bee*>(controller->getGameobjecten().at(0));
		int closedBee = 60000;

		for each (Bee* bee in controller->getGameobjecten())
		{
			if (imkerPos.dist(imkerPos, bee->getPosition()) < closedBee) {
				target = bee;
				closedBee = imkerPos.dist(imkerPos, bee->getPosition());
			}
		}
		_targetPos = graph->getVertexAt(target->getX(), target->getY());
		graph->move(graph->getImker(), _targetPos);
	}
	else {
		graph->move(graph->getImker(), _targetPos);
	}
	
}
