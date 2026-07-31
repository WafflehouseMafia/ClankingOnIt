#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Pathfinding.h"

class PathAgent
{
	glm::vec2 m_position;

	std::vector<AIForGames::Node*> m_path;
	int m_currentIndex;
	AIForGames::Node* m_currentNode;
	float m_speed;

public:
	void Update(float frameTime);
	void GoToNode(AIForGames::Node* node);
	void Draw();
};