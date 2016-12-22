#include "PowerMode.h"
#include "Imker.h"
#include "GoTOBase.h"
#include <vector>
#include "IGameObject.h"
#include "GameController.h"
#include "Vector2D.h"
#include "Bee.h"
#include "string"
#include "Iostream"

PowerMode::PowerMode(Imker * imker)
{
	_imker = imker;
}

PowerMode::~PowerMode()
{
}

void PowerMode::checkState(GameController * controller)
{
	if (_imker->getChatchedBees().size() == 30) {
		_imker->setBehavior(new GoToBase(_imker));
	}
}

void PowerMode::update(GameController * controller)
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

void PowerMode::Move(GameController * controller)
{
}
