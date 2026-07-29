#pragma once
#include "Pathfinding.h"
#include <string>

class NodeMap
{
    int m_width, m_height;
    float m_cellSize;
    AIForGames::Node** m_nodes;
public:
    void Initialise(std::vector<std::string> asciiMap, int cellSize);
    ~NodeMap();
    AIForGames::Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; }
    void Draw();

    static std::vector<AIForGames::Node*> DijkstrasSearch(AIForGames::Node* startNode, AIForGames::Node* endNode);
};
