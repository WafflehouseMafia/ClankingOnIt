#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Pathfinding.h"

class PathAgent
{
	glm::vec2 m_position;

	int m_currentIndex;
	AIForGames::Node* m_currentNode;
	float m_speed;

public:
	std::vector<AIForGames::Node*> m_path;
	void Update(float frameTime);
	void GoToNode(AIForGames::Node* node);
	void Draw();
	void SetNode(AIForGames::Node* start);
	void SetSpeed(float speed);
};