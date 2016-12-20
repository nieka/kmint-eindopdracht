#include "Edge.h"


Edge::Edge(Vertex* vertex1, Vertex* vertex2)
{
	Vector2D v1;
	v1.setX(vertex1->getX());
	v1.sety(vertex1->getY());
	Vector2D v2;
	v2.setX(vertex2->getX());
	v2.sety(vertex2->getY());
	_weigth = v1.dist(v1, v2);

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
