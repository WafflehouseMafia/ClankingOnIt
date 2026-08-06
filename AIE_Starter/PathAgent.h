#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Pathfinding.h"

class PathAgent
{

	int m_currentIndex;
	AIForGames::Node* m_currentNode;
	float m_speed;

public:
	glm::vec2 m_position;
	std::vector<AIForGames::Node*> m_path;
	void Update(float frameTime);
	void PathToNode(AIForGames::Node* node);
	void Draw();
	void SetNode(AIForGames::Node* start);
	void SetSpeed(float speed);
};

