#include "Pathfinding.h"

bool gSortFunction(AIForGames::Node* i, AIForGames::Node* j) { return(i->gScore < j->gScore); }