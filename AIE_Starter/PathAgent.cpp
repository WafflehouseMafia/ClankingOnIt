#include "PathAgent.h"
#include "Pathfinding.h"
#include "NodeMap.h"
#include <cmath>

void PathAgent::Update(float frameTime)
{
	if (sizeof(m_path) == 0)
	{
		return;
	}
	
	AIForGames::Node* next = m_path[m_currentIndex + 1];
	float distanceX = (next->position.x - m_position.x);
	float distanceY = (next->position.y - m_position.y);
	float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));
	distance -= (m_speed * frameTime);
	if (distance > 0)
	{
		float angle = atan2(distanceY, distanceX);// *180 / 3.14159265358979323846;
		m_position.x += ((distance * cos(angle)) * (m_speed * frameTime));
		m_position.y += ((distance * sin(angle)) * (m_speed * frameTime));
		
	}
	else
	{
		m_position.x = next->position.x;
		m_position.y = next->position.y;
		m_currentIndex++;
	}
}

void PathAgent::GoToNode(AIForGames::Node* node)
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
}

void PathAgent::SetSpeed(float speed)
{
	m_speed = speed;
}

