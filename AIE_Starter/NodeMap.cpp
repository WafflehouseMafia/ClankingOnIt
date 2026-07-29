#include "Pathfinding.h"
#include "NodeMap.h"
#include "raylib.h"
#include <string>
#include <iostream>
#include <algorithm>


void NodeMap::Initialise(std::vector <std::string> asciiMap, int cellSize)
{
    m_cellSize = cellSize;
    const char emptySquare = '0';
    m_height = asciiMap.size();
    m_width = asciiMap[0].size();
    m_nodes = new AIForGames::Node * [m_width * m_height];

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
                    node->ConnectTo(nodeWest, 1);
                    nodeWest->ConnectTo(node, 1);
                }

                AIForGames::Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
                if (nodeSouth)
                {
                    node->ConnectTo(nodeSouth, 1);
                    nodeSouth->ConnectTo(node, 1);
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
    Color cellColor = { 84,12,47,255 };
    Color lineColor = { 0,0,0,255 };
    
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            AIForGames::Node* node = GetNode(x, y);
            if (node == nullptr)
            {
                DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize), (int)m_cellSize - 1, (int)m_cellSize - 1, cellColor);
            }
            else
            {
                for (int i = 0; i < node->connections.size(); i++)
                {
                    AIForGames::Node* other = node->connections[i].target;
                    DrawLine((x + 0.5f) * m_cellSize, (y + 0.5f) * m_cellSize, (int)other->position.x, (int)other->position.y, lineColor);
                }
            }
        }
    }
}



static std::vector<AIForGames::Node*> DijkstrasSearch(AIForGames::Node* startNode, AIForGames::Node* endNode)
{
    if (!startNode) { std::cout << "startNode was invalid\n"; abort; }
    if (!endNode) { "endNode was invalid\n"; abort; }
    if (startNode == endNode) { return{}; }
     
    startNode->gScore = 0; startNode->previous = nullptr;

    std::vector<AIForGames::Node*> openList;
    std::vector<AIForGames::Node*> closedList;
    AIForGames::Node* currentNode;
    bool bigIfTrue;

    openList.push_back(startNode);

    while (openList.empty() != true);
    {
        std::sort(openList.begin(), openList.end(), AIForGames::gSortFunction);
        currentNode = openList.front();

        if (currentNode == endNode)
        {
            break;
        }

        openList.erase(openList.begin());
        closedList.push_back(currentNode);

        for (const AIForGames::Edge& c : currentNode->connections)
        {
            if (std::find(closedList.begin(), closedList.end(), c.target) != closedList.end())
            {
                continue;
            }
            if (std::find(openList.begin(), openList.end(), c.target) != openList.end())
            {
                continue;
            }
            c.target->previous = currentNode;
            c.target->gScore = currentNode->gScore + c.cost;
            openList.push_back(c.target);
        }

    } 

    std::vector<AIForGames::Node*> path;
    AIForGames::Node* nextStep = endNode;
    while (nextStep != nullptr)
    {
        path.push_back(nextStep);
        nextStep = nextStep->previous;
    }
    std::reverse(path.begin(), path.end());

    return std::vector<AIForGames::Node*>();
}