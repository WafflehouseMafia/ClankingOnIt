#include "PathAgent.h"
#include "Pathfinding.h"
#include "NodeMap.h"

void PathAgent::Update(float frameTime)
{
	if (sizeof(m_path) == 0)
	{
		return;
	}
	AIForGames::Node* past = m_currentNode;
	m_currentNode = m_path[m_currentIndex];
	
}

void PathAgent::GoToNode(AIForGames::Node* node)
{
	m_path = DijkstrasSearch(m_currentNode, node);
	m_currentIndex = 0;
}

void PathAgent::Draw()
{

}