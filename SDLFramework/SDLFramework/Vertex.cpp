#include "Vertex.h"


Vertex::Vertex(int x, int y)
{
	_x = x;
	_y = y;
}

Vertex::~Vertex()
{
}

void Vertex::addEdge(Edge* edge)
{
	edges.push_back(edge);
}

int Vertex::getX()
{
	return _x;
}

int Vertex::getY()
{
	return _y;
}

void Vertex::setParent(Vertex * parent)
{
	this->parent = parent;
}

void Vertex::setF(int f)
{
	this->f = f;
}

void Vertex::setG(int g)
{
	this->g = g;
}

Vertex * Vertex::getParent()
{
	return parent;
}

bool Vertex::hasImpker() const
{
	return _hasImpker;
}

void Vertex::setImpker(bool impker)
{
	_hasImpker = impker;
}

bool Vertex::hasPowerUP() const
{
	return _hasPowerUp;
}

void Vertex::setPowerUp(bool p)
{
	_hasPowerUp = p;
}

void Vertex::setImpkerGoal(bool g)
{
	_imkerGoal = g;
}

bool Vertex::isImkerGoal() const
{
	return _imkerGoal;
}

int Vertex::getF()
{
	return f;
}

int Vertex::getG()
{
	return g;
}

void Vertex::draw(SDLFacade* app)
{
	if (_imkerGoal)
	{
		app->DrawCircle(getX(), getY(), 7, true);
	}
	else
	{
		app->DrawCircle(getX(), getY(), 5, true);
	}
	
}

std::vector<Edge*> Vertex::getEdges()
{
	return edges;
}
