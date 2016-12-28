#include "Graph.h"
#include <algorithm>
#include <queue>
#include <math.h>  
#include <set>
#include <iostream>
#include <time.h> 
#include "Vector2D.h"

struct compare
{
	bool operator()(Vertex* l, Vertex* r)
	{
		return l->f > r->f;
	}
};

Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::addVertex(Vertex* vertex)
{
	nodes.push_back(vertex);
}

void Graph::addEdge(Edge * edge)
{
	edges.push_back(edge);
}

std::vector<Vertex*> Graph::move(Vertex* start, Vertex* goal)
{
	setImpkerGoal(goal);
	std::vector<Vertex*> cl;

	if (start != goal)
	{
		
		std::priority_queue<Vertex*, std::vector<Vertex*>, compare> ol;
		std::set<Vertex*> set;
		ol.push(start);
		set.insert(start);
		start->setG(0);
		start->setF(_impkerLocation->getG() + heuristic(start, goal));

		while (!ol.empty()) {
			Vertex* current = ol.top();
			ol.pop();
			if (current == goal) {
				//We hebben ons doel berijkt.
				std::cout << "De locatie van de goal is: x= " << goal->getX() << " y= " << goal->getY() << std::endl;
				cl.at(cl.size() - 1)->setParent(current);
				cl.push_back(current);
				return cl;
			}
			cl.push_back(current);
			for each (Vertex* neighbor in getNeighbors(current))
			{
				if (!(std::find(cl.begin(), cl.end(), neighbor) != cl.end())) {
					if (!(std::find(set.begin(), set.end(), neighbor) != set.end())) {
						neighbor->setF(neighbor->getG() + heuristic(neighbor, goal)); // boosdoener
						//neighbor zit nog niet in de openlist
						ol.push(neighbor);
						set.insert(neighbor);
					}
					else {
						Vertex* openingNeighbor = ol.top();
						if (neighbor->getG() < openingNeighbor->getG()) {
							openingNeighbor->setG(neighbor->getG());
							openingNeighbor->setParent(neighbor->getParent());
						}
					}
				}
			}
		}
	}
	return cl;
}

void Graph::draw(SDLFacade * facade)
{
	//draw all edges
	for (int i = 0; i < edges.size(); i++) {
		facade->SetColor(Color(255, 0, 0, 255));
		edges.at(i)->draw(facade);
	}

	//draw all nodes
	for (int i = 0; i < nodes.size(); i++) {
		if (!nodes.at(i)->isImkerGoal()) {
			facade->SetColor(Color(0, 0, 255, 255));
		}
		else {
			facade->SetColor(Color(255, 0, 0, 255));
		}

		nodes.at(i)->draw(facade);

		if (nodes.at(i)->hasPowerUP())
		{
			facade->DrawTexture(_pill, nodes.at(i)->getX(), nodes.at(i)->getY(),25,25);
		}
	}


}

Vertex * Graph::getPowerUp()
{
	return _PowerUp;
}

Vertex * Graph::getImker()
{
	return _impkerLocation;
}

Vertex * Graph::getBase()
{
	return _base;
}

void Graph::setPowerUp(SDLFacade* sdl)
{
	if (_PowerUp == nullptr)
	{
		_pill = sdl->LoadTexture("pill.png");
	}
	else
	{
		_PowerUp->setPowerUp(false);
	}

	srand(time(NULL));
	_PowerUp = nodes[(rand() % nodes.size())];
	_PowerUp->setPowerUp(true);
}

void Graph::setImker(Vertex * loc)
{	
	_impkerLocation = loc;
}

void Graph::setBase(Vertex * base)
{
	_base = base;
}

void Graph::setImpkerGoal(Vertex * goal)
{
	if (_ImpkerGoal != nullptr)
	{
		_ImpkerGoal->setImpkerGoal(false);
	}

	_ImpkerGoal = goal;
	_ImpkerGoal->setImpkerGoal(true);
}

Vertex * Graph::getVertexAt(int x, int y)
{
	int minDist = 60000;
	Vertex* closedVertex = nodes.at(0);
	Vector2D targetlocation;
	targetlocation.setX(x);
	targetlocation.sety(y);

	for each (Vertex* vertex in nodes)
	{
		Vector2D nodeLocation;
		nodeLocation.setX(vertex->getX());
		nodeLocation.sety(vertex->getY());

		if (nodeLocation.dist(nodeLocation, targetlocation) < minDist) {
			minDist = nodeLocation.dist(nodeLocation, targetlocation);
			closedVertex = vertex;
		}
	}


	return closedVertex;
}

int Graph::heuristic(Vertex * start, Vertex * goal)
{
	return sqrt(pow(start->getX() - goal->getX(), 2) + pow(start->getY() - goal->getY(), 2) * 10);
}

void Graph::move(Vertex * node)
{
	if (_impkerLocation != nullptr) {
		_impkerLocation->setImpker(false);
	}
	
	_impkerLocation = _impkerLocation->getParent();
	_impkerLocation->setImpker(true);
	std::cout << "De impker verplaats zich naar positie: x= " << _impkerLocation->getX() << " y= " << _impkerLocation->getY() << std::endl;
	std::cout << "weight: " << _impkerLocation->getF() << std::endl;
}

std::vector<Vertex*> Graph::getNeighbors(Vertex * current)
{
	std::vector<Vertex*> neighbors;
	std::vector<Edge*> edges = current->getEdges();
	for (int i = 0; i < edges.size(); i++)
	{
		Vertex* temp = edges.at(i)->getNeighbor(current);
		temp->setG(current->getG() + edges.at(i)->getWeigth());
		temp->setParent(current);
		neighbors.push_back(temp);
	}

	return neighbors;
}

