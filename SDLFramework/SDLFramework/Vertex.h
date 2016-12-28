#pragma once
#include <vector>
#include "SDLFacade.h"

class Edge;

class Vertex
{
public:
	Vertex(int x, int y);
	~Vertex();
	int getF();
	int getG();
	int f;
	void draw(SDLFacade* app);
	std::vector<Edge*> getEdges();

	void addEdge(Edge * edge);
	int getX();
	int getY();
	void setParent(Vertex * parent);
	void setF(int f);
	void setG(int g);
	Vertex * getParent();
	bool hasImpker() const;
	void setImpker(bool impker);
	bool hasPowerUP() const;
	void setPowerUp(bool p);
	void setImpkerGoal(bool g);
	bool isImkerGoal() const;
	bool connectedTo(Vertex* target);
private:
	int _x;
	int _y;
	std::vector<Edge*> edges;
	Vertex* parent;
	int g;
	bool _hasImpker;
	bool _hasPowerUp;
	bool _imkerGoal;
};

