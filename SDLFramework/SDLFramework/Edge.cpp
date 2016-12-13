#include "Edge.h"


Edge::Edge(Vertex* vertex1, Vertex* vertex2, int weigth)
{
	this->_weigth = weigth;
	vertex1->addEdge(this);
	vertex2->addEdge(this);
	_vertex1 = vertex1;
	_vertex2 = vertex2;
}

Edge::~Edge()
{
}

Vertex * Edge::getVertex1()
{
	return _vertex1;
}

Vertex * Edge::getVertex2()
{
	return _vertex2;
}

Vertex * Edge::getNeighbor(Vertex * other)
{
	if (other->getX() == _vertex1->getX() && other->getY() == _vertex1->getY()) {
		return _vertex2;
	}
	else {
		return _vertex1;
	}
}

void Edge::draw(SDLFacade* app)
{
	app->DrawLine(getVertex1()->getX(), getVertex1()->getY(), getVertex2()->getX(), getVertex2()->getY());
}

int Edge::getWeigth()
{
	return _weigth;
}
