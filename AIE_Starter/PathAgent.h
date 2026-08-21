#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Pathfinding.h"
#include "raylib.h"



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
	void Draw(Color agentColor);
	void SetNode(AIForGames::Node* start);
	void SetSpeed(float speed);
	glm::vec2 GetPosition() { return m_position; }
	void Reset();
};

class Behaviour;
class NodeMap;

class Agent
{
private:
	Behaviour* m_current;
	NodeMap* m_nodeMap;
	Color m_color;
	PathAgent m_pathAgent;
	PathAgent* currentTarget;

public:
	Agent() {};
	Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_color({ 255, 255, 0, 255 }) {}
	~Agent();
	void Update(float deltaTime);
	bool PathComplete();
	void Draw(Color agentColor);
	void GoTo(glm::vec2 point);
	void SetNode(AIForGames::Node* start);
	NodeMap* GetNodeMap() { return m_nodeMap; };
	void SetNodeMap(NodeMap* _nodeMap) { m_nodeMap = _nodeMap; };
	void SetSpeed(float speed);
	void SetColor(Color color);
	Color GetColor() { return m_color; }
	void SetTarget(PathAgent* Target) { currentTarget = Target; }
	PathAgent* GetTarget() { return currentTarget; }
	glm::vec2 GetPosition() { return m_pathAgent.GetPosition(); }

	void Reset();
};

class Agent;

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

class WanderBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);
};

class FollowBehaviour : public Behaviour
{
	glm::vec2 lastTargetPosition;
	
public:
	virtual void Update(Agent* agent, float deltaTime);
	
};

class SelectBehaviour : public Behaviour
{
	Behaviour* stalk;
	Behaviour* wander;
	Behaviour* m_selected;

public:
	SelectBehaviour(Behaviour* b1, Behaviour* b2) : stalk(b1), wander(b2) {}
	~SelectBehaviour() { delete stalk, wander; }
	virtual void Update(Agent* agent, float deltaTime);
	void SetBehaviour(Behaviour* b, Agent* a);
};