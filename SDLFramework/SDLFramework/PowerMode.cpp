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
	moveSteps.clear();
}

PowerMode::~PowerMode()
{
}

void PowerMode::checkState(GameController * controller)
{
	if (_imker->getChatchedBees().size() == 30 || _imker->CatchedAllBees(controller)) {
		_imker->setBehavior(new GoToBase(_imker, "powermode"));
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
		if (imkerPos.dist(imkerPos, bee->getPosition()) <= _imker->getCatchRadius() && !bee->isCathced() && _imker->getChatchedBees().size() < 30) {
			bee->setCathced(true);
			_imker->addcatchedBee(bee);
			std::cout << "Catched a bee" << std::endl;
			std::cout << "Bee's: " << std::to_string(_imker->getChatchedBees().size()) << std::endl;
		}
	}
}

void PowerMode::Move(GameController * controller)
{
	Graph* graph = controller->getGrapth();
	if (canMove(graph)) {
		if (_targetPos == graph->getImker() || _targetPos == nullptr || moveSteps.size() == 0) {
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
			moveSteps = graph->move(graph->getImker(), _targetPos);
			graph->setImpkerGoal(_targetPos);
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
		imkerMovement(*graph);
		imkerMovement(*graph);
	}
}
