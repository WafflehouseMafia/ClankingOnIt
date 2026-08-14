#pragma once
#include "Pathfinding.h"
#include "raylib.h"
#include <string>

class NodeMap
{
    int m_width, m_height;
    float m_cellSize;
    AIForGames::Node** m_nodes;
public:
    void Initialise(std::vector<std::string> asciiMap, int cellSize);
    ~NodeMap();
    void Draw();
    void DrawPath(std::vector<AIForGames::Node*> nodeMapPath, Color lineColor);

    AIForGames::Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; }
    AIForGames::Node* GetClosestNode(glm::vec2 worldPos);
    AIForGames::Node* GetRandomNode();
    float GetCellSize() { return m_cellSize; }
};
