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
}