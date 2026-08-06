#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace AIForGames
{
    struct Node;

    struct Edge {
        Node* target;
        float cost;

        Edge()
        {
            target = nullptr; cost = 0;
        }

        Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}

    };

    struct Node {
        glm::vec2 position{};
        std::vector<Edge> connections;
        float gScore{};
        float hScore{};
        float fScore{};
        Node* previous;

        Node() {}
 
        Node(float x, float y)
        {
            position = { x, y };

        }

        void ConnectTo(Node* othNode, float cost);
    };

    bool gSortFunction(Node* i, Node* j);
    bool fSortFunction(Node* i, Node* j);
    
    std::vector<AIForGames::Node*> DijkstrasSearch(AIForGames::Node* startNode, AIForGames::Node* endNode);

    std::vector<AIForGames::Node*> AStarSearch(AIForGames::Node* startNode, AIForGames::Node* endNode);
}

