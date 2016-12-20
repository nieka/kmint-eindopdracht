#include "Panic.h"
#include "Imker.h"
#include "GoToBase.h"
#include "Graph.h"
#include "GameController.h"

Panic::Panic(Imker* imker)
{
	_imker = imker;
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
	Graph* graph= controller->getGrapth();
	graph->move(graph->getImker(), graph->nodes.at(utils.getRandom(0, graph->nodes.size())));
}
