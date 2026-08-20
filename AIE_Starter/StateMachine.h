#pragma once
#include <vector>


class Behaviour;
class Agent;

class FiniteStateMachine
{

};

class State
{
	std::vector<Behaviour*> m_behaviours;
	std::vector <Transition> m_transitions;
public:
	State();
	~State();
	virtual void Update(Agent* agent, float deltaTime);
	struct Transition
	{
		Condition* condition;
		State* targetState;
	};
};

class Transition
{

};

class Condition
{
	virtual bool IsTrue(Agent* agent) = 0;
};