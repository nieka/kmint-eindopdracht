#pragma once
#include "Vertex.h"
#include "SDLFacade.h"
#include "Vector2D.h"

class Edge
{
public:
	Edge(Vertex* vertex1, Vertex* vertex2);
	~Edge();
	Vertex* getVertex1();
	Vertex* getVertex2();
	Vertex* getNeighbor(Vertex* other);
	void draw(SDLFacade* app);
	int getWeigth();
private:
	int _weigth;
	Vertex* _vertex1;
	Vertex* _vertex2;
};

