#pragma once
#include "PathAgent.h"
#include <vector>

//class Behaviour;
//class Agent;

class Condition;


class State
{
public:
	struct Transition
	{
		Condition* condition;
		State* targetState;
	};
private:
	std::vector<Behaviour*> m_behaviours;
	std::vector <Transition> m_transitions;
public:
	State();
	State(Behaviour* behaviour);
	~State();
	
	virtual void Update(Agent* agent, float deltaTime);
	
	std::vector <Transition> GetTransitions();
};

class FiniteStateMachine : public Behaviour
{
	std::vector<State*> m_states;
	State* m_currentState;
	State* m_newState;
public:
	FiniteStateMachine(State* s) : m_currentState(s), m_newState(nullptr) {}
	virtual ~FiniteStateMachine();
	void Update(Agent* agent, float deltaTime);
};