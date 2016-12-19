#include "ChaseBees.h"
#include <vector>
#include "IGameObject.h"
#include "GameController.h"
#include "Utils.h"
#include "Vector2D.h"
#include "Bee.h"
#include <string>
#include <iostream>


ChaseBees::ChaseBees(Imker* imker)
{
	_imker = imker;
}


ChaseBees::~ChaseBees()
{
}

void ChaseBees::checkState()
{
	if (_catchedBees == 10) {
		//verander state
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
			_catchedBees++;
			std::cout << std::to_string(_catchedBees) << std::endl;
		}
	}

}
