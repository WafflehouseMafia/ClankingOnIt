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

}