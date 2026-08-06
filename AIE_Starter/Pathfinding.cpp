#include "Pathfinding.h"
#include <iostream>
#include <algorithm>
#include <cmath>

bool AIForGames::gSortFunction(AIForGames::Node* i, AIForGames::Node* j) { return(i->gScore < j->gScore); }
bool AIForGames::fSortFunction(AIForGames::Node* i, AIForGames::Node* j) { return(i->fScore < j->fScore); }

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
            float gScore = currentNode->gScore + c.cost;
            if (std::find(openList.begin(), openList.end(), c.target) == openList.end())
            {
                c.target->previous = currentNode;
                c.target->gScore = gScore;
                openList.push_back(c.target);
            }
            else if (gScore < c.target->gScore)
            {
                c.target->previous = currentNode;
                c.target->gScore = gScore;
            }
            
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

std::vector<AIForGames::Node*> AIForGames::AStarSearch(AIForGames::Node* startNode, AIForGames::Node* endNode)
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
        std::sort(openList.begin(), openList.end(), fSortFunction);
        //std::sort(openList.begin(), openList.end(), gSortFunction);
        currentNode = openList.front();

        if (currentNode == endNode)
            break;

        openList.erase(openList.begin());
        closedList.push_back(currentNode);

        for (const Edge& c : currentNode->connections)
        {
            if (std::find(closedList.begin(), closedList.end(), c.target) == closedList.end())
            {
                float gScore = currentNode->gScore + c.cost;
                //c.target->gScore = gScore;
                float hScore = std::abs(c.target->position.x - endNode->position.x) + std::abs(c.target->position.y - endNode->position.y);
                //c.target->hScore = hScore;
                float fScore = gScore + hScore;
                //c.target->fScore = fScore;

                if (std::find(openList.begin(), openList.end(), c.target) == openList.end())
                {
                    c.target->gScore = gScore;
                    c.target->fScore = fScore;
                    c.target->previous = currentNode;
                    openList.push_back(c.target);
                }
                else if (fScore < c.target->fScore)
                {
                    c.target->gScore = gScore;
                    c.target->fScore = fScore;
                    c.target->previous = currentNode;
                }
            }
            
        }

    }

    std::vector<Node*> path;
    currentNode = endNode;
    while (currentNode != nullptr)
    {
        path.insert(path.begin(), currentNode);
        currentNode = currentNode->previous;
    }
    //std::reverse(path.begin(), path.end());

    return path;
}