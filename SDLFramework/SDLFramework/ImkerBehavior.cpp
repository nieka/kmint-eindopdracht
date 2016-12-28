#include "IIMkerBehavior.h"
#include "Imker.h"
#include "Graph.h"
#include <iostream>
#include <string>

bool ImkerBehavior::canMove(Graph* graph) {
	if (graph->getImker()->getX() == _imker->getX() && graph->getImker()->getY() == _imker->getY()) {
		return true;
	}
	else {
		return false;
	}
}

void ImkerBehavior::imkerMovement(Graph & graph)
{
	if (_imker->getX() < graph.getImker()->getX())
	{
		_imker->setX(_imker->getX() + 1);
	}
	else if (_imker->getX() > graph.getImker()->getX())
	{
		_imker->setX(_imker->getX() - 1);
	}

	if (_imker->getY() < graph.getImker()->getY())
	{
		_imker->setY(_imker->getY() + 1);
	}
	else if (_imker->getY() > graph.getImker()->getY())
	{
		_imker->setY(_imker->getY() - 1);
	}
}
