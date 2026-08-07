#include "Pathfinding.h"
#include "NodeMap.h"
#include "raylib.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <map>


void NodeMap::Initialise(std::vector <std::string> asciiMap, int cellSize)
{
    m_cellSize = cellSize;
    const char emptySquare = '0';
    m_height = asciiMap.size();
    m_width = asciiMap[0].size();
    m_nodes = new AIForGames::Node * [m_width * m_height];
    std::map<char, float> tileCost
    {
        {'1', 1.0f},
        {'3', 3.0f},
        {'5', 5.0f}
    };

    for (int y = 0; y < m_height; y++)
    {
        std::string& line = asciiMap[y];
        if (line.size() != m_width)
            std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")\n";
        for (int x = 0; x < m_width; x++)
        {
            char tile = x < line.size() ? line[x] : emptySquare;
            m_nodes[x + m_width * y] = tile == emptySquare ? nullptr
                : new AIForGames::Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);

            AIForGames::Node* node = GetNode(x, y);
            if (node)
            {

                
                AIForGames::Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
                if (nodeWest)
                {
                    glm::vec2 betweenNodes = { nodeWest->position - node->position };
                    float Celldistance = glm::length(betweenNodes);
                    char westTile = asciiMap[y][x - 1];
                    float nodeCost = tileCost[tile];
                    float westCost = tileCost[westTile];
                    float averageCost = (nodeCost + westCost) / 2;
                    
                    node->ConnectTo(nodeWest, Celldistance * averageCost);
                    nodeWest->ConnectTo(node, Celldistance * averageCost);
                }

                AIForGames::Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
                if (nodeSouth)
                {
                    glm::vec2 betweenNodes = { nodeSouth->position - node->position };
                    float Celldistance = glm::length(betweenNodes);
                    char southTile = asciiMap[y - 1][x];
                    float nodeCost = tileCost[tile];
                    float southCost = tileCost[southTile];
                    float averageCost = (nodeCost + southCost) / 2;

                    node->ConnectTo(nodeSouth, Celldistance * averageCost);
                    nodeSouth->ConnectTo(node, Celldistance * averageCost);
                }
            }
        }
    }

}

NodeMap::~NodeMap()
{

}

void AIForGames::Node::ConnectTo(Node* othNode, float cost)
{
    connections.push_back(Edge(othNode, cost));
}

void NodeMap::Draw()
{
    Color wallColor = { 84,12,47,255 };
    Color lineColor = { 0,0,0,255 };
    
    
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            AIForGames::Node* node = GetNode(x, y);
            if (node == nullptr)
            {
                DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize), (int)m_cellSize - 1, (int)m_cellSize - 1, wallColor);
            }
            else
            {
                for (int i = 0; i < node->connections.size(); i++)
                {
                    AIForGames::Node* other = node->connections[i].target;
                    //Color cellColor = { 130, 130, 130, (255 * node->gScore) };
                    DrawLine((x + 0.5f) * m_cellSize, (y + 0.5f) * m_cellSize, (int)other->position.x, (int)other->position.y, lineColor);
                    //DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize), (int)m_cellSize - 1, (int)m_cellSize - 1, cellColor);
                    
                }
            }
        }
    }
}

void NodeMap::DrawPath(std::vector<AIForGames::Node*> nodeMapPath, Color lineColor)
{
    for (int i = 1; i < nodeMapPath.size(); i++)
    {
        AIForGames::Node* other = nodeMapPath[i]->previous;
        DrawLine(nodeMapPath[i]->position.x, nodeMapPath[i]->position.y, other->position.x, other->position.y, lineColor);
    }
}

AIForGames::Node* NodeMap::GetClosestNode(glm::vec2 worldPos)
{
    int x = (int)(worldPos.x / m_cellSize);
    if (x < 0 || x >= m_width) { return nullptr; }
    int y = (int)(worldPos.y / m_cellSize);
    if (y < 0 || y >= m_height) { return nullptr; }

    return GetNode(x, y);
}