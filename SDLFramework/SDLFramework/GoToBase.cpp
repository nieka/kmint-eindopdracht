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
		_imker->setBehavior(new ChaseBees(_imker));
	}
}

void GoToBase::update(GameController * controller)
{
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

void GoToBase::Move(GameController * controller)
{
	Graph* graph = controller->getGrapth();
	graph->move(graph->getImker(), graph->getBase());
}
