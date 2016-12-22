#include "GoToBase.h"
#include "ChaseBees.h"

GoToBase::GoToBase(Imker* imker)
{
	_imker = imker;
}


GoToBase::~GoToBase()
{
}

void GoToBase::checkState(GameController * controller)
{
	Graph* graph = controller->getGrapth();
	if (graph->getImker() == graph->getBase())
	{
		_imker->deliverbees();
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
	graph->move(graph->getImker(), graph->getBase());
}
