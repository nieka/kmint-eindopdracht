#include "GoToBase.h"
#include "ChaseBees.h"

GoToBase::GoToBase(Imker* imker, std::string laststate)
{
	_imker = imker;
	moveSteps.clear();
	_lastState = laststate;
}


GoToBase::~GoToBase()
{
}

void GoToBase::checkState(GameController * controller)
{
	Graph* graph = controller->getGrapth();
	if (graph->getImker() == graph->getBase())
	{
		reflection();
		_imker->deliverbees(controller);
		_imker->setBehavior(new ChaseBees(_imker));
	}
}

void GoToBase::update(GameController * controller)
{
}

void GoToBase::Move(GameController * controller)
{
	Graph* graph = controller->getGrapth();
	if (canMove(graph)) {
		if (moveSteps.size() == 0) {
			moveSteps = graph->move(graph->getImker(), graph->getBase());
			graph->setImpkerGoal(graph->getBase());
		}
		else {
			Vertex* loc = moveSteps.at(0);
			loc->setImpker(true);
			graph->setImker(loc);
			moveSteps.erase(moveSteps.begin(), moveSteps.begin() + 1);
		}
	}
	else {
		imkerMovement(*graph);
	}	
}

void GoToBase::reflection()
{
	//evaluatie
	if (_imker->getChatchedBees().size() > 0)
	{
		if (_lastState == "chasingbees") // chasing bees
		{
			if (_imker->getReturnToBase() < 40)
			{
				_imker->setReturnToBase(_imker->getReturnToBase() + 3);
				if (_imker->getReturnToBase() > 40)
				{
					_imker->setReturnToBase(40);
				}
			}
		}
		else if (_lastState == "powermode") // powermode
		{
			if (_imker->getCollectPowerUp() < 40)
			{
				_imker->setCollectPowerUp(_imker->getCollectPowerUp() + 3);
				if (_imker->getCollectPowerUp() > 40)
				{
					_imker->setCollectPowerUp(40);
				}
			}
		}
	}
	else // panic mode
	{
		//als de imker geen bijen heeft gevangen en panic mode heeft gehad 
		//dan verhoogt hij de kans van zowel powermode als return to base zodat de kans van panic mode lager wordt.
		if (_imker->getReturnToBase() < 40)
		{
			_imker->setReturnToBase(_imker->getReturnToBase() + 3);
			if (_imker->getReturnToBase() > 40)
			{
				_imker->setReturnToBase(40);
			}
		}

		if (_imker->getCollectPowerUp() < 40)
		{
			_imker->setCollectPowerUp(_imker->getCollectPowerUp() + 3);
			if (_imker->getCollectPowerUp() > 40)
			{
				_imker->setCollectPowerUp(40);
			}
		}
	}
}
