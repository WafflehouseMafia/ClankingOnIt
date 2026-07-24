#pragma once
#include "Pathfinding.h"
#include <string>

using namespace AIForGames;

class NodeMap
{
    int m_width, m_height;
    float m_cellSize;
    Node** m_nodes;
public:
    void Initialise(std::vector<std::string> asciiMap, int cellSize);
    ~NodeMap();
    Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; }
    void Draw();

    static std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);
};
