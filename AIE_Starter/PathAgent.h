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

class Agent
{
	PathAgent m_pathAgent;
	Behaviour* m_current;
	NodeMap* m_nodeMap;
	Color m_color;

public:
	Agent() {};
	Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_color({ 255, 255, 0, 255 }) {}
	~Agent() { delete m_current; }
	void Update(float deltaTime);
	void Draw();
	void GoTo(glm::vec2 point);
};

class Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime) = 0;
};

class GoToPointBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);
};