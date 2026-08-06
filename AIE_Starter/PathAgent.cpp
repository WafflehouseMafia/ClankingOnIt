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
	m_path = DijkstrasSearch(m_currentNode, node);
	m_currentIndex = 0;
}

void PathAgent::Draw()
{
	Color agentColor = { 30, 110, 20, 255 };
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

