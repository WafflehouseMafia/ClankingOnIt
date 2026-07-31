#include "Pathfinding.h"
#include <iostream>
#include <algorithm>

bool AIForGames::gSortFunction(AIForGames::Node* i, AIForGames::Node* j) { return(i->gScore < j->gScore); }

std::vector<AIForGames::Node*> AIForGames::DijkstrasSearch(AIForGames::Node* startNode, AIForGames::Node* endNode)
{
    if (!startNode) { std::cout << "startNode was invalid\n"; abort(); }
    if (!endNode) { std::cout << "endNode was invalid\n"; abort(); }
    if (startNode == endNode) { return{}; }

    startNode->gScore = 0; startNode->previous = nullptr;

    std::vector<Node*> openList;
    std::vector<Node*> closedList;
    Node* currentNode = nullptr;

    openList.push_back(startNode);

    while (openList.empty() != true)
    {
        std::sort(openList.begin(), openList.end(), gSortFunction);
        currentNode = openList.front();

        if (currentNode == endNode)
            break;


        openList.erase(openList.begin());
        closedList.push_back(currentNode);

        for (const Edge& c : currentNode->connections)
        {
            if (std::find(closedList.begin(), closedList.end(), c.target) != closedList.end())
            {
                continue;
            }
            if (std::find(openList.begin(), openList.end(), c.target) == openList.end())
            {
                c.target->previous = currentNode;
                c.target->gScore = currentNode->gScore + c.cost;
                openList.push_back(c.target);
            }
            //c.target->previous = currentNode;
            //c.target->gScore = currentNode->gScore + c.cost;
            //openList.push_back(c.target);
        }

    }

    std::vector<Node*> path;
    Node* nextStep = endNode;
    while (nextStep != nullptr)
    {
        path.insert(path.begin(), nextStep);
        nextStep = nextStep->previous;
    }
    //std::reverse(path.begin(), path.end());

    return path;
}