#include "StateMachine.h"
#include "PathAgent.h"

State::State()
{

}

State::~State()
{
	for (Behaviour* b : m_behaviours)
	{
		delete b;
	}

	for (Transition t : m_transitions)
	{
		delete t.condition;
	}
}

void State::Update(Agent* agent, float deltaTime)
{
	for (Behaviour* b : m_behaviours)
	{
		b->Update(agent, deltaTime);
	}
}

std::vector <State::Transition> State::GetTransitions()
{
	return m_transitions;
}

FiniteStateMachine::~FiniteStateMachine()
{
	for (State* s : m_states)
	{
		delete s;
	}
}

void FiniteStateMachine::Update(Agent* agent, float deltaTime)
{
	m_currentState->Update(agent, deltaTime);
}
