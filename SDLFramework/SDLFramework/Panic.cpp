#include "Panic.h"
#include "Imker.h"
#include "GoToBase.h"
#include "Graph.h"
#include "GameController.h"
#include "Bee.h"

Panic::Panic(Imker* imker)
{
	_imker = imker;
	moveSteps.clear();
}


Panic::~Panic()
{
}

void Panic::checkState(GameController * controller)
{
	if (_imker->getChatchedBees().size() == 0) {
		_imker->setBehavior(new GoToBase(_imker));
	}
}

void Panic::update(GameController * controller)
{
	if (utils.getRandom(0, 10) < 3) {
		_imker->getChatchedBees().pop_back();
	}
}

void Panic::Move(GameController * controller)
{
	Graph* graph = controller->getGrapth();
	if (_targetPos == graph->getImker() || _targetPos == nullptr || moveSteps.size() == 0) {
		Vector2D imkerPos;
		imkerPos.setX(_imker->getX());
		imkerPos.sety(_imker->getY());
		Bee* target = dynamic_cast<Bee*>(controller->getGameobjecten().at(0));
		int distanceToBee = 0;

		for each (Bee* bee in controller->getGameobjecten())
		{
			if (imkerPos.dist(imkerPos, bee->getPosition()) > distanceToBee) {
				target = bee;
				distanceToBee = imkerPos.dist(imkerPos, bee->getPosition());
			}
		}

		Vector2D targetVector;
		if (target->getX() < 300) {
			targetVector.setX(600);
		}
		else {
			targetVector.setX(0);
		}
		targetVector.sety(target->getY());
		
		_targetPos = graph->getVertexAt(targetVector.getX(), targetVector.getY());

		moveSteps = graph->move(graph->getImker(), _targetPos);
	}
	else {
		Vertex* loc = moveSteps.at(0);
		loc->setImpker(true);
		graph->setImker(loc);
		moveSteps.erase(moveSteps.begin(), moveSteps.begin() + 1);
	}
	
	
}
