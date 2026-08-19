#pragma once

class Behaviour;
class Agent;

class FiniteStateMachine
{

};

class State
{
	std::vector<Behaviour*> m_behaviours;
public:
	State();
	~State() {};
	virtual void Update(Agent* agent, float deltaTime);
};

class Transition
{

};

class Condition
{
	virtual bool IsTrue(Agent* agent) = 0;
};