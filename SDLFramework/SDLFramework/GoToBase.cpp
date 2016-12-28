#include "GoToBase.h"
#include "ChaseBees.h"

GoToBase::GoToBase(Imker* imker)
{
	_imker = imker;
	moveSteps.clear();
}


GoToBase::~GoToBase()
{
}

void GoToBase::checkState(GameController * controller)
{
	Graph* graph = controller->getGrapth();
	if (graph->getImker() == graph->getBase())
	{
		_imker->deliverbees(controller);
		//TODO evaluatie
		_imker->setBehavior(new ChaseBees(_imker));
	}
}

void GoToBase::update(GameController * controller)
{
}

void GoToBase::Move(GameController * controller)
{
	Graph* graph = controller->getGrapth();
	if (moveSteps.size() == 0) {
		graph->move(graph->getImker(), graph->getBase());
	}
	else {
		Vertex* loc = moveSteps.at(0);
		loc->setImpker(true);
		graph->setImker(loc);
		moveSteps.erase(moveSteps.begin(), moveSteps.begin() + 1);
	}
	
}
