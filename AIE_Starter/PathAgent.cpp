#include "PathAgent.h"
#include "Pathfinding.h"
#include "NodeMap.h"
#include <cmath>

void PathAgent::Update(float frameTime)
{

	if (m_path.size() == 0)
	{
		return;
	}
	
	AIForGames::Node* next = m_path[m_currentIndex];
	glm::vec2 moveDirection = { next->position - m_position };
	float distance = glm::length(moveDirection);
	distance -= (m_speed * frameTime);
	if (distance > 0)
	{
		m_position += glm::normalize(moveDirection) * distance * m_speed * frameTime;
	}
	else
	{
		m_position = next->position;
		m_currentNode = m_path[m_currentIndex];
		m_currentIndex++;
		if (m_currentIndex == m_path.size())
		{
			m_path.clear();
		}
	}
}

void PathAgent::PathToNode(AIForGames::Node* node)
{
	m_path = AStarSearch(m_currentNode, node);
	m_currentIndex = 0;
}

void PathAgent::Draw(Color agentColor)
{
	DrawCircle(m_position.x, m_position.y, 5, agentColor);
}

void PathAgent::SetNode(AIForGames::Node* start)
{
	m_position = start->position;
	m_currentNode = start;
}

void PathAgent::SetSpeed(float speed)
{
	m_speed = speed;
}

void Agent::SetColor(Color a)
{
	m_color = a;
}

void Agent::Update(float deltaTime)
{
	if (m_current)
	{
	    m_current->Update(this, deltaTime);
	}
	m_pathAgent.Update(deltaTime);
		
}

void GoToPointBehaviour::Update(Agent* agent, float deltaTime)
{
	if (IsMouseButtonPressed(0))
	{
		Vector2 mousePos = GetMousePosition();
		agent->GoTo(glm::vec2(mousePos.x, mousePos.y));
	}
}

void Agent::GoTo(glm::vec2 point)
{
	
	AIForGames::Node* end = m_nodeMap->GetClosestNode(point);
	m_pathAgent.PathToNode(end);
}

void Agent::Draw(Color agentColor)
{
	m_pathAgent.Draw(agentColor);
}

void Agent::SetNode(AIForGames::Node* start)
{
	m_pathAgent.SetNode(start);
}

bool Agent::PathComplete()
{
	return m_pathAgent.m_path.empty();
}

void WanderBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->PathComplete())
	{
		NodeMap* nodeMap = agent->GetNodeMap();
		AIForGames::Node* end = nodeMap->GetRandomNode();
	    agent->GoTo(end->position);
	}
}

Agent::~Agent() { delete m_current; }

void Agent::SetSpeed(float speed)
{
	m_pathAgent.SetSpeed(speed);
}

void FollowBehaviour::Update(Agent* agent, float deltaTime)
{
	PathAgent* target = agent->GetTarget();
	if (target)
	{
		float dist = glm::distance(target->m_position, lastTargetPosition);
		if (dist > agent->GetNodeMap()->GetCellSize())
		{
			lastTargetPosition = target->m_position;
			agent->GoTo(lastTargetPosition);
		}
	}
	

}

void SelectBehaviour::SetBehaviour(Behaviour* b, Agent* a)
{
	if (m_selected != b)
	{
		m_selected = b;
		a->Reset();
	}
}

void SelectBehaviour::Update(Agent* agent, float deltaTime)
{
	if (glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) < agent->GetNodeMap()->GetCellSize() * 5)
	{
		SetBehaviour(stalk, agent);
		agent->SetColor({ 145, 25, 90, 255 });
	}
	else
	{
		SetBehaviour(wander, agent);
		agent->SetColor({ 200, 80, 10, 255 });
	}
	m_selected->Update(agent, deltaTime);
}

void PathAgent::Reset()
{
	m_path.clear();
}

void Agent::Reset()
{
	m_pathAgent.Reset();
}
