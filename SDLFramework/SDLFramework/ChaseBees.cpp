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
	if (_imker->getChatchedBees().size() == 10) {
		//verander state
		Utils utils;
		int value = utils.getRandom(0, 100);
		int derde = 100 / 3;
		if (value <= derde) {
			std::cout << "behaviour: Collect Power up" << std::endl;
			_imker->setBehavior(new CollectPowerUp(_imker));
		}
		else if (value <= derde * 2) {
			std::cout << "behaviour: Go to Base" << std::endl;
			_imker->setBehavior(new GoToBase(_imker));
		}
		else {
			std::cout << "behaviour: Panic" << std::endl;
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
			std::cout << "Catched a bee" << std::endl;
			std::cout << "Bee's: " << std::to_string(_imker->getChatchedBees().size()) << std::endl;
		}
	}
}

void ChaseBees::Move(GameController* controller)
{
	Graph* graph = controller->getGrapth();
	//TODO calculate closest bee

}
